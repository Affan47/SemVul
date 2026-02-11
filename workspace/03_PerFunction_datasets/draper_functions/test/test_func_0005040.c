validate_gimple_arglist (const_gimple call, ...)
{
  enum tree_code code;
  bool res = 0;
  va_list ap;
  const_tree arg;
  size_t i;

  va_start (ap, call);
  i = 0;

  do
    {
      code = (enum tree_code) va_arg (ap, int);
      switch (code)
	{
	case 0:

	  res = true;
	  goto end;
	case VOID_TYPE:


	  res = (i == gimple_call_num_args (call));
	  goto end;
	default:


	  arg = gimple_call_arg (call, i++);
	  if (!validate_arg (arg, code))
	    goto end;
	  break;
	}
    }
  while (1);


 end: ;
  va_end (ap);

  return res;
}
