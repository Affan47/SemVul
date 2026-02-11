hp_clear_keys(HP_SHARE *info)
{
  uint key;
  DBUG_ENTER("hp_clear_keys");

  for (key=0 ; key < info->keys ; key++)
  {
    HP_KEYDEF *keyinfo = info->keydef + key;
    if (keyinfo->algorithm == HA_KEY_ALG_BTREE)
    {
      delete_tree(&keyinfo->rb_tree);
    }
    else
    {
      HP_BLOCK *block= &keyinfo->block;
      if (block->levels)
        (void) hp_free_level(block,block->levels,block->root,(uchar*) 0);
      block->levels=0;
      block->last_allocated=0;
      keyinfo->hash_buckets= 0;
    }
  }
  info->index_length=0;
  DBUG_VOID_RETURN;
}
