find_vinsn_conflicts (vliw_insn *vinsn)
{
  int i, j;
  int branches = 0;
  xtensa_isa isa = xtensa_default_isa;

  gas_assert (!past_xtensa_end);

  for (i = 0 ; i < vinsn->num_slots; i++)
    {
      TInsn *op1 = &vinsn->slots[i];
      if (op1->is_specific_opcode)
	op1->keep_wide = TRUE;
      else
	op1->keep_wide = FALSE;
    }

  for (i = 0 ; i < vinsn->num_slots; i++)
    {
      TInsn *op1 = &vinsn->slots[i];

      if (xtensa_opcode_is_branch (isa, op1->opcode) == 1)
	branches++;

      for (j = 0; j < vinsn->num_slots; j++)
	{
	  if (i != j)
	    {
	      TInsn *op2 = &vinsn->slots[j];
	      char conflict_type = check_t1_t2_reads_and_writes (op1, op2);
	      switch (conflict_type)
		{
		case 'c':
		  as_bad (_("opcodes '%s' (slot %d) and '%s' (slot %d) write the same register"),
			  xtensa_opcode_name (isa, op1->opcode), i,
			  xtensa_opcode_name (isa, op2->opcode), j);
		  return TRUE;
		case 'd':
		  as_bad (_("opcodes '%s' (slot %d) and '%s' (slot %d) write the same state"),
			  xtensa_opcode_name (isa, op1->opcode), i,
			  xtensa_opcode_name (isa, op2->opcode), j);
		  return TRUE;
		case 'e':
		  as_bad (_("opcodes '%s' (slot %d) and '%s' (slot %d) write the same port"),
			  xtensa_opcode_name (isa, op1->opcode), i,
			  xtensa_opcode_name (isa, op2->opcode), j);
		  return TRUE;
		case 'f':
		  as_bad (_("opcodes '%s' (slot %d) and '%s' (slot %d) both have volatile port accesses"),
			  xtensa_opcode_name (isa, op1->opcode), i,
			  xtensa_opcode_name (isa, op2->opcode), j);
		  return TRUE;
		default:

		  break;
		}
	      op2->is_specific_opcode = (op2->is_specific_opcode
					 || conflict_type == 'a');
	    }
	}
    }

  if (branches > 1)
    {
      as_bad (_("multiple branches or jumps in the same bundle"));
      return TRUE;
    }

  return FALSE;
}
