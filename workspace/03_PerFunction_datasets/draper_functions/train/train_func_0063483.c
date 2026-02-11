report_swap()
{
  int cnt;

  long *errors;
  void *pnt;
  int i;
  int gotErrors = 0;
  char **errormsg = NULL;


  if((cnt = fetch_table(MEM_INDEX_MIB, null_callback, NULL, 0)) < 0)
  {
    printf("%s: Could not fetch mem index\n", bn);
    return STATE_UNKNOWN;
  }

  if(!cnt)
  {
    printf("%s: Not configure.\n", bn);
    return STATE_WARNING;
  }


  if(!(errors  = calloc(sizeof(long), cnt)))
  {
    printf("%s: Could not allocate memory for information\n", bn);
    return STATE_CRITICAL;
  }

  pnt = errors;
  if(fetch_table(MEM_ERRORFLAG_MIB, integer_callback, pnt, cnt) < 0)
  {
    printf("%s: Could not fetch error list!\n", bn);
    return STATE_UNKNOWN;
  }

  for(i=0; i<cnt; i++)
  {
    if(verbose)
      printf("%s: Got Flag %ld for %d\n", bn, errors[i], i);

    if(errors[i])
    {
      gotErrors = 1;
      break;
    }
  }

  errormsg = calloc(sizeof(char **), cnt);
  if(!errormsg)
  {
    printf("%s: Could not allocate memory for error information\n", bn);
    return STATE_CRITICAL;
  }

  pnt = errormsg;

  if(fetch_table(MEM_ERRORMSG_MIB, string_callback, pnt, cnt) < 0)
  {
    printf("%s: Could not fetch error messages\n", bn);
    return STATE_CRITICAL;
  }

  for(i=0; i < cnt; i++)
  {
    if(errors[i])
      printf("%s\n", errormsg[i]);
  }

  if(gotErrors == 0)
  {
	printf("Checked memory for %d entries.\n", cnt);
    return STATE_OK;
  }

  return STATE_CRITICAL;
}
