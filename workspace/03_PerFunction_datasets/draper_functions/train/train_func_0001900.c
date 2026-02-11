maybe_hot_frequency_p (int freq)
{
  struct cgraph_node *node = cgraph_get_node (current_function_decl);
  if (!profile_info || !flag_branch_probabilities)
    {
      if (node->frequency == NODE_FREQUENCY_UNLIKELY_EXECUTED)
        return false;
      if (node->frequency == NODE_FREQUENCY_HOT)
        return true;
    }
  if (profile_status == PROFILE_ABSENT)
    return true;
  if (node->frequency == NODE_FREQUENCY_EXECUTED_ONCE
      && freq < (ENTRY_BLOCK_PTR->frequency * 2 / 3))
    return false;
  if (freq < ENTRY_BLOCK_PTR->frequency / PARAM_VALUE (HOT_BB_FREQUENCY_FRACTION))
    return false;
  return true;
}
