parse_gc(ESL_MSA *msa, char *buf)
{
  char *gc;
  char *tag;
  char *text;
  char *s;
  int   len;
  int   status;

  s = buf;
  if (esl_strtok    (&s, " \t\n\r", &gc)               != eslOK) return eslEFORMAT;
  if (esl_strtok    (&s, " \t\n\r", &tag)              != eslOK) return eslEFORMAT;
  if (esl_strtok_adv(&s, " \t\n\r", &text, &len, NULL) != eslOK) return eslEFORMAT;

  if      (strcmp(tag, "SS_cons") == 0)  status = esl_strcat(&(msa->ss_cons), -1, text, len);
  else if (strcmp(tag, "SA_cons") == 0)  status = esl_strcat(&(msa->sa_cons), -1, text, len);
  else if (strcmp(tag, "PP_cons") == 0)  status = esl_strcat(&(msa->pp_cons), -1, text, len);
  else if (strcmp(tag, "RF")      == 0)  status = esl_strcat(&(msa->rf),      -1, text, len);
  else if (strcmp(tag, "MM")      == 0)  status = esl_strcat(&(msa->mm),      -1, text, len);
  else                                   status = esl_msa_AppendGC(msa, tag, text);

  return status;
}
