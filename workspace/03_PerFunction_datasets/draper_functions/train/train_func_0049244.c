get_arguments()
{
  if (error)
    return 1;
  char *to= num_buffer;
  uint str_count=0;
  for (uint i=0; i < f_args.arg_count; i++)
  {
    f_args.args[i]=0;
    switch (f_args.arg_type[i]) {
    case STRING_RESULT:
    case DECIMAL_RESULT:
      {
	String *res=args[i]->val_str(&buffers[str_count++]);
	if (!(args[i]->null_value))
	{
	  f_args.args[i]=    (char*) res->ptr();
	  f_args.lengths[i]= res->length();
	  break;
	}
      }
    case INT_RESULT:
      *((longlong*) to) = args[i]->val_int();
      if (!args[i]->null_value)
      {
	f_args.args[i]=to;
	to+= ALIGN_SIZE(sizeof(longlong));
      }
      break;
    case REAL_RESULT:
      *((double*) to)= args[i]->val_real();
      if (!args[i]->null_value)
      {
	f_args.args[i]=to;
	to+= ALIGN_SIZE(sizeof(double));
      }
      break;
    case ROW_RESULT:
    default:

      DBUG_ASSERT(0);
      break;
    }
  }
  return 0;
}
