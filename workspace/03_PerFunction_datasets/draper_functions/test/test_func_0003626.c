arm_function_ok_for_sibcall (tree decl, tree exp)
{
  unsigned long func_type;

  if (cfun->machine->sibcall_blocked)
    return false;


  if (decl == NULL || TARGET_THUMB1)
    return false;


  if (TARGET_VXWORKS_RTP && flag_pic && !targetm.binds_local_p (decl))
    return false;


  if (arm_is_long_call_p (decl))
    return false;


  if (TARGET_INTERWORK && TREE_PUBLIC (decl) && !TREE_ASM_WRITTEN (decl))
    return false;

  func_type = arm_current_func_type ();

  if (IS_INTERRUPT (func_type))
    return false;

  if (!VOID_TYPE_P (TREE_TYPE (DECL_RESULT (cfun->decl))))
    {


      rtx a, b;

      a = arm_function_value (TREE_TYPE (exp), decl, false);
      b = arm_function_value (TREE_TYPE (DECL_RESULT (cfun->decl)),
			      cfun->decl, false);
      if (!rtx_equal_p (a, b))
	return false;
    }


  if (IS_STACKALIGN (func_type))
    return false;


  if (TARGET_AAPCS_BASED
      && arm_abi == ARM_ABI_AAPCS
      && DECL_WEAK (decl))
    return false;


  return true;
}
