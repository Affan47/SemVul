_mi_check_index(MI_INFO *info, int inx)
{
  if (inx == -1)
    inx=info->lastinx;
  if (inx < 0)
  {
    my_errno= HA_ERR_WRONG_INDEX;
    return -1;
  }
  if (!mi_is_key_active(info->s->state.key_map, inx))
  {
    my_errno= info->s->state.state.records ? HA_ERR_WRONG_INDEX :
                                             HA_ERR_END_OF_FILE;
    return -1;
  }
  if (info->lastinx != inx)
  {
    info->lastinx = inx;
    info->page_changed=1;
    info->update= ((info->update & (HA_STATE_CHANGED | HA_STATE_ROW_CHANGED)) |
                   HA_STATE_NEXT_FOUND | HA_STATE_PREV_FOUND);
  }
  if (info->opt_flag & WRITE_CACHE_USED && flush_io_cache(&info->rec_cache))
    return(-1);
  return(inx);
}
