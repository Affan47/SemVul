expand_builtin_printf (tree arglist, rtx target, enum machine_mode mode,
		       bool unlocked)
{


  tree const fn_putchar = unlocked ? built_in_decls[BUILT_IN_PUTCHAR_UNLOCKED]
    : implicit_built_in_decls[BUILT_IN_PUTCHAR];
  tree const fn_puts = unlocked ? built_in_decls[BUILT_IN_PUTS_UNLOCKED]
    : implicit_built_in_decls[BUILT_IN_PUTS];
  const char *fmt_str;
  tree fn, fmt, arg;


  if (target != const0_rtx)
    return 0;


  if (! arglist)
    return 0;
  fmt = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (fmt)) != POINTER_TYPE)
    return 0;
  arglist = TREE_CHAIN (arglist);


  fmt_str = c_getstr (fmt);
  if (fmt_str == NULL)
    return 0;


  if (strcmp (fmt_str, "%s\n") == 0)
    {
      if (! arglist
          || TREE_CODE (TREE_TYPE (TREE_VALUE (arglist))) != POINTER_TYPE
	  || TREE_CHAIN (arglist))
	return 0;
      fn = fn_puts;
    }

  else if (strcmp (fmt_str, "%c") == 0)
    {
      if (! arglist
	  || TREE_CODE (TREE_TYPE (TREE_VALUE (arglist))) != INTEGER_TYPE
	  || TREE_CHAIN (arglist))
	return 0;
      fn = fn_putchar;
    }
  else
    {

      if (strchr (fmt_str, '%'))
        return 0;

      if (arglist)
	return 0;


      if (fmt_str[0] == '\0')
	return const0_rtx;

      if (fmt_str[1] == '\0')
	{


	  arg = build_int_2 (fmt_str[0], 0);
	  arglist = build_tree_list (NULL_TREE, arg);
	  fn = fn_putchar;
	}
      else
	{

	  size_t len = strlen (fmt_str);
	  if (fmt_str[len - 1] == '\n')
	    {


	      char *newstr = (char *) alloca (len);
	      memcpy (newstr, fmt_str, len - 1);
	      newstr[len - 1] = 0;

	      arg = build_string_literal (len, newstr);
	      arglist = build_tree_list (NULL_TREE, arg);
	      fn = fn_puts;
	    }
	  else


	    return 0;
	}
    }

  if (!fn)
    return 0;
  return expand_expr (build_function_call_expr (fn, arglist),
		      target, mode, EXPAND_NORMAL);
}
