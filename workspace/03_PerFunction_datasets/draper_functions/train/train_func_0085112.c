view_checksum(THD *thd, TABLE_LIST *view)
{
  char md5[MD5_BUFF_LENGTH];
  if (!view->view || view->md5.length != 32)
    return HA_ADMIN_NOT_IMPLEMENTED;
  view->calc_md5(md5);
  return (strncmp(md5, view->md5.str, 32) ?
          HA_ADMIN_WRONG_CHECKSUM :
          HA_ADMIN_OK);
}
