maybe_hot_bb_p (const_basic_block bb)
{
  if (profile_status == PROFILE_READ)
    return maybe_hot_count_p (bb->count);
  return maybe_hot_frequency_p (bb->frequency);
}
