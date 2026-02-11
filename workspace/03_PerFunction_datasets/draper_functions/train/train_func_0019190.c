irplib_paf_dump_string( char *key, const char * value,
					   const char *comment, FILE *paf )
{
  cpl_ensure_code(paf,   CPL_ERROR_NULL_INPUT);
  cpl_ensure_code(key,   CPL_ERROR_NULL_INPUT);
  cpl_ensure_code(value, CPL_ERROR_NULL_INPUT);

  if (comment == NULL)
    cpl_ensure_code(fprintf(paf, PAF_KEY_FORMAT "\"%s\"\n",
			    key, value) > PAF_KEY_LEN,
		    CPL_ERROR_FILE_IO);
  else
    cpl_ensure_code(fprintf(paf, PAF_KEY_FORMAT "\"%s\" ; # %s\n",
			    key, value, comment) > PAF_KEY_LEN,
		    CPL_ERROR_FILE_IO);

  return CPL_ERROR_NONE;
}
