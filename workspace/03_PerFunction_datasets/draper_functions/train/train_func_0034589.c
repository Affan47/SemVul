call_insn_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 88 "/home/dcharvest/ubuntu64-builder/genericMake/build/toolchain/dl/gcc-4.7.4/gcc/config/xtensa/predicates.md"
{
  if ((GET_CODE (op) == REG)
      && (op != arg_pointer_rtx)
      && ((REGNO (op) < FRAME_POINTER_REGNUM)
	  || (REGNO (op) > LAST_VIRTUAL_REGISTER)))
    return true;

  if (CONSTANT_ADDRESS_P (op))
    {

      if (flag_pic)
	{
	  tree callee, callee_sec, caller_sec;

	  if (GET_CODE (op) != SYMBOL_REF
	      || !SYMBOL_REF_LOCAL_P (op) || SYMBOL_REF_EXTERNAL_P (op))
	    return false;


	  if (flag_function_sections
	      || DECL_ONE_ONLY (current_function_decl))
	    return false;
	  caller_sec = DECL_SECTION_NAME (current_function_decl);
	  callee = SYMBOL_REF_DECL (op);
	  if (callee)
	    {
	      if (DECL_ONE_ONLY (callee))
		return false;
	      callee_sec = DECL_SECTION_NAME (callee);
	      if (((caller_sec == NULL_TREE) ^ (callee_sec == NULL_TREE))
		  || (caller_sec != NULL_TREE
		      && strcmp (TREE_STRING_POINTER (caller_sec),
				 TREE_STRING_POINTER (callee_sec)) != 0))
		return false;
	    }
	  else if (caller_sec != NULL_TREE)
	    return false;
	}
      return true;
    }

  return false;
}
