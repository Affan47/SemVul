gap_frame_fetch_unregister_user(gint32 ffetch_user_id)
{
  gint32 count_active_users;
  GapFFetchResourceUserElem *usr_ptr;

  if(gap_debug)
  {
    printf("gap_frame_fetch_unregister_user: UNREGISTER ffetch_user_id:%d pid:%d\n"
          , ffetch_user_id
          , (int) gap_base_getpid()
          );
  }

  count_active_users = 0;
  for(usr_ptr = global_rsource_users; usr_ptr != NULL; usr_ptr = (GapFFetchResourceUserElem *)usr_ptr->next)
  {
    if (ffetch_user_id == usr_ptr->ffetch_user_id)
    {
      usr_ptr->ffetch_user_id = -1;
    }
    else if (usr_ptr->ffetch_user_id >= 0)
    {
      count_active_users++;
    }
  }

  if(count_active_users == 0)
  {
    if(gap_debug)
    {
      printf("gap_frame_fetch_unregister_user: no more resource users, DROP cached duplicates and video handles\n");
    }
    gap_frame_fetch_delete_list_of_duplicated_images(-1);
#ifdef GAP_ENABLE_VIDEOAPI_SUPPORT
    p_drop_vidhandle_cache();
#endif
  }

}
