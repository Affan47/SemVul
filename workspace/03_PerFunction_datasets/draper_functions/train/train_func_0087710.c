get_inv_cost (struct invariant *inv, int *comp_cost, unsigned *regs_needed)
{
  int i, acomp_cost;
  unsigned aregs_needed[N_REG_CLASSES];
  unsigned depno;
  struct invariant *dep;
  bitmap_iterator bi;


  inv = VEC_index (invariant_p, invariants, inv->eqto);

  *comp_cost = 0;
  if (! flag_ira_loop_pressure)
    regs_needed[0] = 0;
  else
    {
      for (i = 0; i < ira_pressure_classes_num; i++)
	regs_needed[ira_pressure_classes[i]] = 0;
    }

  if (inv->move
      || inv->stamp == actual_stamp)
    return;
  inv->stamp = actual_stamp;

  if (! flag_ira_loop_pressure)
    regs_needed[0]++;
  else
    {
      int nregs;
      enum reg_class pressure_class;

      pressure_class = get_pressure_class_and_nregs (inv->insn, &nregs);
      regs_needed[pressure_class] += nregs;
    }

  if (!inv->cheap_address
      || inv->def->n_addr_uses < inv->def->n_uses)
    (*comp_cost) += inv->cost;

#ifdef STACK_REGS
  {


    rtx set = single_set (inv->insn);
    if (set
	&& IS_STACK_MODE (GET_MODE (SET_SRC (set)))
	&& constant_pool_constant_p (SET_SRC (set)))
      {
	if (flag_ira_loop_pressure)
	  regs_needed[ira_stack_reg_pressure_class] += 2;
	else
	  regs_needed[0] += 2;
      }
  }
#endif

  EXECUTE_IF_SET_IN_BITMAP (inv->depends_on, 0, depno, bi)
    {
      bool check_p;

      dep = VEC_index (invariant_p, invariants, depno);

      get_inv_cost (dep, &acomp_cost, aregs_needed);

      if (! flag_ira_loop_pressure)
	check_p = aregs_needed[0] != 0;
      else
	{
	  for (i = 0; i < ira_pressure_classes_num; i++)
	    if (aregs_needed[ira_pressure_classes[i]] != 0)
	      break;
	  check_p = i < ira_pressure_classes_num;
	}
      if (check_p


	  && dep->always_executed
	  && !dep->def->uses->next)
	{


	  if (! flag_ira_loop_pressure)
	    aregs_needed[0]--;
	  else
	    {
	      int nregs;
	      enum reg_class pressure_class;

	      pressure_class = get_pressure_class_and_nregs (inv->insn, &nregs);
	      aregs_needed[pressure_class] -= nregs;
	    }
	}

      if (! flag_ira_loop_pressure)
	regs_needed[0] += aregs_needed[0];
      else
	{
	  for (i = 0; i < ira_pressure_classes_num; i++)
	    regs_needed[ira_pressure_classes[i]]
	      += aregs_needed[ira_pressure_classes[i]];
	}
      (*comp_cost) += acomp_cost;
    }
}
