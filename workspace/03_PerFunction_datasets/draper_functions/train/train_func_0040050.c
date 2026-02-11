esl_sqfile_OpenDigital(const ESL_ALPHABET *abc, const char *filename, int format, const char *env, ESL_SQFILE **ret_sqfp)
{
  int status;

  if ((status = sqfile_open(filename, format, env, ret_sqfp)) != eslOK) return status;
  return esl_sqfile_SetDigital(*ret_sqfp, abc);
}
