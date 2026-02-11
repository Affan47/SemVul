const_ok_for_output_1 (rtx *rtlp, void *data ATTRIBUTE_UNUSED)
{
  rtx rtl = *rtlp;

  if (GET_CODE (rtl) == UNSPEC)
    {


#ifdef ENABLE_CHECKING


      if (XVECLEN (rtl, 0) != 1
	  || GET_CODE (XVECEXP (rtl, 0, 0)) != SYMBOL_REF
	  || SYMBOL_REF_DECL (XVECEXP (rtl, 0, 0)) == NULL
	  || TREE_CODE (SYMBOL_REF_DECL (XVECEXP (rtl, 0, 0))) != VAR_DECL
	  || !DECL_THREAD_LOCAL_P (SYMBOL_REF_DECL (XVECEXP (rtl, 0, 0))))
	inform (current_function_decl
		? DECL_SOURCE_LOCATION (current_function_decl)
		: UNKNOWN_LOCATION,
#if NUM_UNSPEC_VALUES > 0
		"non-delegitimized UNSPEC %s (%d) found in variable location",
		((XINT (rtl, 1) >= 0 && XINT (rtl, 1) < NUM_UNSPEC_VALUES)
		 ? unspec_strings[XINT (rtl, 1)] : "unknown"),
		XINT (rtl, 1));
#else
		"non-delegitimized UNSPEC %d found in variable location",
		XINT (rtl, 1));
#endif
#endif
      expansion_failed (NULL_TREE, rtl,
			"UNSPEC hasn't been delegitimized.\n");
      return 1;
    }

  if (targetm.const_not_ok_for_debug_p (rtl))
    {
      expansion_failed (NULL_TREE, rtl,
			"Expression rejected for debug by the backend.\n");
      return 1;
    }

  if (GET_CODE (rtl) != SYMBOL_REF)
    return 0;

  if (CONSTANT_POOL_ADDRESS_P (rtl))
    {
      bool marked;
      get_pool_constant_mark (rtl, &marked);


      if (!marked)
	{
	  expansion_failed (NULL_TREE, rtl,
			    "Constant was removed from constant pool.\n");
	  return 1;
	}
    }

  if (SYMBOL_REF_TLS_MODEL (rtl) != TLS_MODEL_NONE)
    return 1;


  if (SYMBOL_REF_EXTERNAL_P (rtl))
    {
      tree decl = SYMBOL_REF_DECL (rtl);

      if (decl == NULL || !targetm.binds_local_p (decl))
	{
	  expansion_failed (NULL_TREE, rtl,
			    "Symbol not defined in current TU.\n");
	  return 1;
	}
    }

  return 0;
}
