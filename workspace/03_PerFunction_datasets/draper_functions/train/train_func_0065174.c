ira_better_spill_reload_regno_p (int *regnos, int *other_regnos,
				 rtx in, rtx out, rtx insn)
{
  int cost, other_cost;
  int length, other_length;
  int nrefs, other_nrefs;
  int call_used_count, other_call_used_count;
  int hard_regno, other_hard_regno;

  cost = calculate_spill_cost (regnos, in, out, insn,
			       &length, &nrefs, &call_used_count, &hard_regno);
  other_cost = calculate_spill_cost (other_regnos, in, out, insn,
				     &other_length, &other_nrefs,
				     &other_call_used_count,
				     &other_hard_regno);
  if (nrefs == 0 && other_nrefs != 0)
    return true;
  if (nrefs != 0 && other_nrefs == 0)
    return false;
  if (cost != other_cost)
    return cost < other_cost;
  if (length != other_length)
    return length > other_length;
#ifdef REG_ALLOC_ORDER
  if (hard_regno >= 0 && other_hard_regno >= 0)
    return (inv_reg_alloc_order[hard_regno]
	    < inv_reg_alloc_order[other_hard_regno]);
#else
  if (call_used_count != other_call_used_count)
    return call_used_count > other_call_used_count;
#endif
  return false;
}
