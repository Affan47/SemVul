gap_player_cache_insert(const gchar *ckey
                      , GapPlayerCacheData *cdata)
{
  GapPlayerCacheAdmin *admin_ptr;
  gint32               new_bytesize;
  GapPlayerCacheElem  *new_elem_ptr;

  if((ckey == NULL) || (cdata == NULL))
  {
    return;
  }

  if(gap_debug)
  {
    printf("gap_player_cache_insert: ckey:<%s>\n", ckey);
    p_debug_printf_cdata(cdata);
  }

  if(gap_player_cache_lookup(ckey) != NULL)
  {
    if(gap_debug)
    {
      printf("gap_player_cache_insert: INSERT REJECTED! ckey:<%s> \n", ckey);
    }
    return;
  }

  new_elem_ptr = p_new_elem(ckey, cdata);
  new_bytesize = p_get_elem_size(new_elem_ptr);
  admin_ptr = p_get_admin_ptr();

  p_player_cache_shrink(admin_ptr, new_bytesize);
  p_player_cache_add_new_frame(admin_ptr, new_elem_ptr);

}
