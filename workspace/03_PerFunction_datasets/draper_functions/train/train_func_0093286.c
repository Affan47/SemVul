tilespec_reread_callback(struct option *poption)
{
  const char *tileset_name = option_str_get(poption);

  fc_assert_ret(NULL != tileset_name && tileset_name[0] != '\0');
  tilespec_reread(tileset_name, TRUE);
  menus_init();
}
