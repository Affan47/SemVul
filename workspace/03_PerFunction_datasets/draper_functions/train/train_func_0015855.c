xtensa_fold_builtin (tree fndecl, int n_args ATTRIBUTE_UNUSED, tree *args,
		     bool ignore ATTRIBUTE_UNUSED)
{
  unsigned int fcode = DECL_FUNCTION_CODE (fndecl);
  tree arg0, arg1;

  switch (fcode)
    {
    case XTENSA_BUILTIN_UMULSIDI3:
      arg0 = args[0];
      arg1 = args[1];
      if ((TREE_CODE (arg0) == INTEGER_CST && TREE_CODE (arg1) == INTEGER_CST)
	  || TARGET_MUL32_HIGH)
	return fold_build2 (MULT_EXPR, unsigned_intDI_type_node,
			    fold_convert (unsigned_intDI_type_node, arg0),
			    fold_convert (unsigned_intDI_type_node, arg1));
      break;

    case XTENSA_BUILTIN_THREAD_POINTER:
    case XTENSA_BUILTIN_SET_THREAD_POINTER:
      break;

    default:
      internal_error ("bad builtin code");
      break;
    }

  return NULL;
}
