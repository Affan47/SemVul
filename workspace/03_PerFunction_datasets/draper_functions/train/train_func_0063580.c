p_player_cache_shrink(GapPlayerCacheAdmin *admin_ptr, gint32 new_bytesize)
{
  while(admin_ptr->start_elem != NULL)
  {


    if((admin_ptr->summary_bytesize + new_bytesize) < admin_ptr->configured_max_bytesize)
    {
      if(gap_debug)
      {
        printf("p_player_cache_shrink: SPACE OK %d\n", (int)admin_ptr->summary_bytesize);
      }
      break;
    }
    p_player_cache_remove_oldest_frame(admin_ptr);
  }
}
