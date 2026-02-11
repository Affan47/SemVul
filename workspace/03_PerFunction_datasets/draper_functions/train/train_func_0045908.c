validate_header (ValidateContext  *ctx,
		 GError          **error)
{
  GITypelib *typelib = ctx->typelib;

  if (!validate_header_basic (typelib->data, typelib->len, error))
    return FALSE;

  {
    Header *header = (Header*)typelib->data;
    if (!validate_name (typelib, "namespace", typelib->data, header->namespace, error))
      return FALSE;
  }

  return TRUE;
}
