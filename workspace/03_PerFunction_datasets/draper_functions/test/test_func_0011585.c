function_types_compatible_p (f1, f2)
     tree f1, f2;
{
  tree args1, args2;

  int val = 1;
  int val1;

  if (!(TREE_TYPE (f1) == TREE_TYPE (f2)
	|| (val = comptypes (TREE_TYPE (f1), TREE_TYPE (f2)))))
    return 0;

  args1 = TYPE_ARG_TYPES (f1);
  args2 = TYPE_ARG_TYPES (f2);


  if (args1 == 0)
    {
      if (!self_promoting_args_p (args2))
	return 0;


      if (TYPE_ACTUAL_ARG_TYPES (f1)
	  && 1 != type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1)))
	val = 2;
      return val;
    }
  if (args2 == 0)
    {
      if (!self_promoting_args_p (args1))
	return 0;
      if (TYPE_ACTUAL_ARG_TYPES (f2)
	  && 1 != type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2)))
	val = 2;
      return val;
    }


  val1 = type_lists_compatible_p (args1, args2);
  return val1 != 1 ? val1 : val;
}
