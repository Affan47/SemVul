open(const char *name, int mode, uint test_if_locked)
{
  internal_table= test(test_if_locked & HA_OPEN_INTERNAL_TABLE);
  if (internal_table || (!(file= heap_open(name, mode)) && my_errno == ENOENT))
  {
    HP_CREATE_INFO create_info;
    my_bool created_new_share;
    int rc;
    file= 0;
    if (heap_prepare_hp_create_info(table, internal_table, &create_info))
      goto end;
    create_info.pin_share= TRUE;

    rc= heap_create(name, &create_info, &internal_share, &created_new_share);
    my_free(create_info.keydef);
    if (rc)
      goto end;

    implicit_emptied= test(created_new_share);
    if (internal_table)
      file= heap_open_from_share(internal_share, mode);
    else
      file= heap_open_from_share_and_register(internal_share, mode);

    if (!file)
    {
      heap_release_share(internal_share, internal_table);
      goto end;
    }
  }

  ref_length= sizeof(HEAP_PTR);

  set_keys_for_scanning();


  key_stat_version= file->s->key_stat_version-1;
end:
  return (file ? 0 : 1);
}
