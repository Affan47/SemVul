expand_builtin_va_arg (valist, type)
     tree valist, type;
{
  rtx addr, result;
  tree promoted_type, want_va_type, have_va_type;


  want_va_type = va_list_type_node;
  have_va_type = TREE_TYPE (valist);
  if (TREE_CODE (want_va_type) == ARRAY_TYPE)
    {


      if (TREE_CODE (have_va_type) == ARRAY_TYPE
	  || TREE_CODE (have_va_type) == POINTER_TYPE)
	{
	  want_va_type = TREE_TYPE (want_va_type);
	  have_va_type = TREE_TYPE (have_va_type);
	}
    }
  if (TYPE_MAIN_VARIANT (want_va_type) != TYPE_MAIN_VARIANT (have_va_type))
    {
      error ("first argument to `va_arg' not of type `va_list'");
      addr = const0_rtx;
    }


  else if ((promoted_type = (*lang_hooks.types.type_promotes_to) (type))
	   != type)
    {
      const char *name = "<anonymous type>", *pname = 0;
      static bool gave_help;

      if (TYPE_NAME (type))
	{
	  if (TREE_CODE (TYPE_NAME (type)) == IDENTIFIER_NODE)
	    name = IDENTIFIER_POINTER (TYPE_NAME (type));
	  else if (TREE_CODE (TYPE_NAME (type)) == TYPE_DECL
		   && DECL_NAME (TYPE_NAME (type)))
	    name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type)));
	}
      if (TYPE_NAME (promoted_type))
	{
	  if (TREE_CODE (TYPE_NAME (promoted_type)) == IDENTIFIER_NODE)
	    pname = IDENTIFIER_POINTER (TYPE_NAME (promoted_type));
	  else if (TREE_CODE (TYPE_NAME (promoted_type)) == TYPE_DECL
		   && DECL_NAME (TYPE_NAME (promoted_type)))
	    pname = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (promoted_type)));
	}


      warning ("`%s' is promoted to `%s' when passed through `...'",
	       name, pname);
      if (! gave_help)
	{
	  gave_help = true;
	  warning ("(so you should pass `%s' not `%s' to `va_arg')",
		   pname, name);
	}


      expand_builtin_trap ();


      addr = const0_rtx;
    }
  else
    {


      valist = stabilize_va_list (valist, 0);

#ifdef EXPAND_BUILTIN_VA_ARG
      addr = EXPAND_BUILTIN_VA_ARG (valist, type);
#else
      addr = std_expand_builtin_va_arg (valist, type);
#endif
    }

#ifdef POINTERS_EXTEND_UNSIGNED
  if (GET_MODE (addr) != Pmode)
    addr = convert_memory_address (Pmode, addr);
#endif

  result = gen_rtx_MEM (TYPE_MODE (type), addr);
  set_mem_alias_set (result, get_varargs_alias_set ());

  return result;
}
