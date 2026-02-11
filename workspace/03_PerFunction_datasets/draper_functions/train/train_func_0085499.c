bypass_block (bb, setcc, jump)
     basic_block bb;
     rtx setcc, jump;
{
  rtx insn, note;
  edge e, enext, edest;
  int i, change;

  insn = (setcc != NULL) ? setcc : jump;


  reg_use_count = 0;
  note_uses (&PATTERN (insn), find_used_regs, NULL);
  note = find_reg_equal_equiv_note (insn);
  if (note)
    find_used_regs (&XEXP (note, 0), NULL);

  change = 0;
  for (e = bb->pred; e; e = enext)
    {
      enext = e->pred_next;
      for (i = 0; i < reg_use_count; i++)
	{
	  struct reg_use *reg_used = &reg_use_table[i];
	  unsigned int regno = REGNO (reg_used->reg_rtx);
	  basic_block dest, old_dest;
	  struct expr *set;
	  rtx src, new;

	  if (regno >= max_gcse_regno)
	    continue;

	  set = find_bypass_set (regno, e->src->index);

	  if (! set)
	    continue;


	  if (e->insns && reg_killed_on_edge (reg_used->reg_rtx, e))
	    continue;

	  src = SET_SRC (pc_set (jump));

	  if (setcc != NULL)
	      src = simplify_replace_rtx (src,
					  SET_DEST (PATTERN (setcc)),
					  SET_SRC (PATTERN (setcc)));

	  new = simplify_replace_rtx (src, reg_used->reg_rtx,
				      SET_SRC (set->expr));


	  if (new == pc_rtx)
	    {
	      edest = FALLTHRU_EDGE (bb);
	      dest = edest->insns ? NULL : edest->dest;
	    }
	  else if (GET_CODE (new) == LABEL_REF)
	    {
	      dest = BLOCK_FOR_INSN (XEXP (new, 0));

	      for (edest = bb->succ; edest; edest = edest->succ_next)
		if (edest->dest == dest && edest->insns)
		  {
		    dest = NULL;
		    break;
		  }
	    }
	  else
	    dest = NULL;


	  old_dest = e->dest;
	  if (dest != NULL && dest != old_dest
	      && redirect_edge_and_branch (e, dest))
	    {


	      if (setcc)
		{
		  rtx pat = PATTERN (setcc);
		  if (!CC0_P (SET_DEST (pat)))
		    insert_insn_on_edge (copy_insn (pat), e);
		}

	      if (gcse_file != NULL)
		{
		  fprintf (gcse_file, "JUMP-BYPASS: Proved reg %d in jump_insn %d equals constant ",
			   regno, INSN_UID (jump));
		  print_rtl (gcse_file, SET_SRC (set->expr));
		  fprintf (gcse_file, "\nBypass edge from %d->%d to %d\n",
			   e->src->index, old_dest->index, dest->index);
		}
	      change = 1;
	      break;
	    }
	}
    }
  return change;
}
