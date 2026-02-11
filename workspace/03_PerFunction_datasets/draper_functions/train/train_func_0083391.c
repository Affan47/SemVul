check_const_len_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1)
  {
    strmov(message, "CHECK_CONST_LEN accepts only one argument");
    return 1;
  }
  if (args->args[0] == 0)
  {
    initid->ptr= (char*)"Not constant";
  }
  else if(strlen(args->args[0]) == args->lengths[0])
  {
    initid->ptr= (char*)"Correct length";
  }
  else
  {
    initid->ptr= (char*)"Wrong length";
  }
  initid->max_length = 100;
  return 0;
}
