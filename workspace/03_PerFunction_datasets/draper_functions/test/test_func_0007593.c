BranchCondition(HHasInstanceTypeAndBranch* instr) {
  InstanceType from = instr->from();
  InstanceType to = instr->to();
  if (from == to) return equal;
  if (to == LAST_TYPE) return above_equal;
  if (from == FIRST_TYPE) return below_equal;
  UNREACHABLE();
  return equal;
}
