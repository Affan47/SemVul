esl_regexp_MultipleMatches(ESL_REGEXP *machine, char **sptr)
{
  int status;

  status = regexec(machine->ndfa, *sptr);
  if (status == eslOK)
    *sptr = machine->ndfa->endp[0];
  else
    *sptr = NULL;
  return status;
}
