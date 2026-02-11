mi_reset(MI_INFO *info)
{
  int error= 0;
  MYISAM_SHARE *share=info->s;
  DBUG_ENTER("mi_reset");


  if (info->opt_flag & (READ_CACHE_USED | WRITE_CACHE_USED))
  {
    info->opt_flag&= ~(READ_CACHE_USED | WRITE_CACHE_USED);
    error= end_io_cache(&info->rec_cache);
  }
  if (share->base.blobs)
    mi_alloc_rec_buff(info, -1, &info->rec_buff);
#if defined(HAVE_MMAP) && defined(HAVE_MADVISE)
  if (info->opt_flag & MEMMAP_USED)
    madvise((char*) share->file_map, share->state.state.data_file_length,
            MADV_RANDOM);
#endif
  info->opt_flag&= ~(KEY_READ_USED | REMEMBER_OLD_POS);
  info->quick_mode=0;
  info->lastinx= 0;
  info->last_search_keypage= info->lastpos= HA_OFFSET_ERROR;
  info->page_changed= 1;
  info->update= ((info->update & HA_STATE_CHANGED) | HA_STATE_NEXT_FOUND |
                 HA_STATE_PREV_FOUND);
  DBUG_RETURN(error);
}
