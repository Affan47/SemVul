TrioFormatRef(trio_reference_t *reference,
	      TRIO_CONST char *format,
	      va_list arglist,
	      void **argarray)
{
  int status;
  trio_parameter_t parameters[MAX_PARAMETERS];

  status = TrioParse(TYPE_PRINT, format, parameters, arglist, argarray);
  if (status < 0)
    return status;

  status = TrioFormatProcess(reference->data, format, parameters);
  if (reference->data->error != 0)
    {
      status = reference->data->error;
    }
  return status;
}
