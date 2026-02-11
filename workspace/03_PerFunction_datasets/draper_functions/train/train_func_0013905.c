validate_function_blob (ValidateContext *ctx,
			guint32        offset,
			guint16        container_type,
			GError       **error)
{
  GITypelib *typelib = ctx->typelib;
  FunctionBlob *blob;

  if (typelib->len < offset + sizeof (FunctionBlob))
    {
      g_set_error (error,
		   G_TYPELIB_ERROR,
		   G_TYPELIB_ERROR_INVALID,
		   "The buffer is too short");
      return FALSE;
    }

  blob = (FunctionBlob*) &typelib->data[offset];

  if (blob->blob_type != BLOB_TYPE_FUNCTION)
    {
      g_set_error (error,
		   G_TYPELIB_ERROR,
		   G_TYPELIB_ERROR_INVALID_BLOB,
		   "Wrong blob type %d, expected function", blob->blob_type);
      return FALSE;
    }

  if (!validate_name (typelib, "function", typelib->data, blob->name, error))
    return FALSE;

  push_context (ctx, get_string_nofail (typelib, blob->name));

  if (!validate_name (typelib, "function symbol", typelib->data, blob->symbol, error))
    return FALSE;

  if (blob->constructor)
    {
      switch (container_type)
	{
	case BLOB_TYPE_BOXED:
	case BLOB_TYPE_STRUCT:
	case BLOB_TYPE_UNION:
	case BLOB_TYPE_OBJECT:
	case BLOB_TYPE_INTERFACE:
	  break;
	default:
	  g_set_error (error,
		       G_TYPELIB_ERROR,
		       G_TYPELIB_ERROR_INVALID_BLOB,
		       "Constructor not allowed");
	  return FALSE;
	}
    }

  if (blob->setter || blob->getter || blob->wraps_vfunc)
    {
      switch (container_type)
	{
	case BLOB_TYPE_OBJECT:
	case BLOB_TYPE_INTERFACE:
	  break;
	default:
	  g_set_error (error,
		       G_TYPELIB_ERROR,
		       G_TYPELIB_ERROR_INVALID_BLOB,
		       "Setter, getter or wrapper not allowed");
	  return FALSE;
	}
    }

  if (blob->index)
    {
      if (!(blob->setter || blob->getter || blob->wraps_vfunc))
	{
	  g_set_error (error,
		       G_TYPELIB_ERROR,
		       G_TYPELIB_ERROR_INVALID_BLOB,
		       "Must be setter, getter or wrapper");
	  return FALSE;
	}
    }


  if (!validate_signature_blob (typelib, blob->signature, error))
    return FALSE;

  if (blob->constructor)
    {
      SimpleTypeBlob *simple = return_type_from_signature (typelib,
							   blob->signature,
							   error);
      InterfaceTypeBlob *iface_type;

      if (!simple)
	return FALSE;
      iface_type = get_type_blob (typelib, simple, error);
      if (!iface_type)
	return FALSE;
      if (iface_type->tag != GI_TYPE_TAG_INTERFACE &&
          (container_type == BLOB_TYPE_OBJECT ||
           container_type == BLOB_TYPE_INTERFACE))
	{
	  g_set_error (error,
		       G_TYPELIB_ERROR,
		       G_TYPELIB_ERROR_INVALID,
		       "Invalid return type '%s' for constructor '%s'",
		       g_type_tag_to_string (iface_type->tag),
		       get_string_nofail (typelib, blob->symbol));
	  return FALSE;
	}
    }

  pop_context (ctx);

  return TRUE;
}
