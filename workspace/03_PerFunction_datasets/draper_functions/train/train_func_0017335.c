find_record_with_key(struct file_info *file_info, uchar *record)
{
  uint key;
  MI_INFO *info=file_info->isam;
  uchar tmp_key[MI_MAX_KEY_BUFF];

  for (key=0 ; key < info->s->base.keys ; key++)
  {
    if (mi_is_key_active(info->s->state.key_map, key) &&
	info->s->keyinfo[key].flag & HA_NOSAME)
    {
      (void) _mi_make_key(info,key,tmp_key,record,0L);
      return mi_rkey(info,file_info->record,(int) key,tmp_key,0,
		     HA_READ_KEY_EXACT);
    }
  }
  return 1;
}
