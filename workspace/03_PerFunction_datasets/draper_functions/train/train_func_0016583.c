heap_disable_indexes(HP_INFO *info)
{
  HP_SHARE *share= info->s;

  if (share->keys)
  {
    hp_clear_keys(share);
    share->currently_disabled_keys= share->keys;
    share->keys= 0;
  }
  return 0;
}
