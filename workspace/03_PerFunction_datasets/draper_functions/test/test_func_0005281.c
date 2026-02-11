compare_strands(bool strandsignA, bool strandsignB)
{
  if (strandsignA && !strandsignB)
    return -1;
  if (!strandsignA && strandsignB)
    return 1;
  return 0;
}
