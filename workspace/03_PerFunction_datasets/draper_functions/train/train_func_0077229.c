gss_import_name (OM_uint32 * minor_status,
		 const gss_buffer_t input_name_buffer,
		 const gss_OID input_name_type, gss_name_t * output_name)
{
  if (!output_name)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_BAD_NAME | GSS_S_CALL_INACCESSIBLE_WRITE;
    }

  *output_name = malloc (sizeof (**output_name));
  if (!*output_name)
    {
      if (minor_status)
	*minor_status = ENOMEM;
      return GSS_S_FAILURE;
    }
  (*output_name)->length = input_name_buffer->length;
  (*output_name)->value = malloc (input_name_buffer->length);
  if (!(*output_name)->value)
    {
      free (*output_name);
      if (minor_status)
	*minor_status = ENOMEM;
      return GSS_S_FAILURE;
    }
  memcpy ((*output_name)->value,
	  input_name_buffer->value, input_name_buffer->length);

  (*output_name)->type = input_name_type;

  if (minor_status)
    *minor_status = 0;
  return GSS_S_COMPLETE;
}
