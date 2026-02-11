update_ld_motion_stores (struct expr * expr)
{
  struct ls_expr * mem_ptr;

  if ((mem_ptr = find_rtx_in_ldst (expr->expr)))
    {


      rtx list = mem_ptr->stores;

      for ( ; list != NULL_RTX; list = XEXP (list, 1))
	{
	  rtx insn = XEXP (list, 0);
	  rtx pat = PATTERN (insn);
	  rtx src = SET_SRC (pat);
	  rtx reg = expr->reaching_reg;
	  rtx copy;


	  if (expr->reaching_reg == src)
	    continue;

	  if (dump_file)
	    {
	      fprintf (dump_file, "PRE:  store updated with reaching reg ");
	      print_rtl (dump_file, reg);
	      fprintf (dump_file, ":\n	");
	      print_inline_rtx (dump_file, insn, 8);
	      fprintf (dump_file, "\n");
	    }

	  copy = gen_move_insn (reg, copy_rtx (SET_SRC (pat)));
	  emit_insn_before (copy, insn);
	  SET_SRC (pat) = reg;
	  df_insn_rescan (insn);


	  INSN_CODE (insn) = -1;
	  gcse_create_count++;
	}
    }
}
