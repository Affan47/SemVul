gc_sound_policy_set(int policy)
{
  switch (policy)
    {
    case PLAY_ONLY_IF_IDLE : sound_policy = PLAY_ONLY_IF_IDLE; break;
    case PLAY_AFTER_CURRENT : sound_policy = PLAY_AFTER_CURRENT; break;
    case PLAY_AND_INTERRUPT : sound_policy = PLAY_AND_INTERRUPT; break;
    default : sound_policy = PLAY_AFTER_CURRENT;
    }
}
