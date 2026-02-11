check_for_label_ref (rtx *rtl, void *data)
{
  rtx insn = (rtx) data;


  return (GET_CODE (*rtl) == LABEL_REF
	  && ! LABEL_REF_NONLOCAL_P (*rtl)
	  && (!JUMP_P (insn)
	      || !label_is_jump_target_p (XEXP (*rtl, 0), insn))
	  && LABEL_P (XEXP (*rtl, 0))
	  && INSN_UID (XEXP (*rtl, 0)) != 0
	  && ! find_reg_note (insn, REG_LABEL_OPERAND, XEXP (*rtl, 0)));
}
