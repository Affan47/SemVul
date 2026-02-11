xmp_tags_initialize ()
{
  static GOnce my_once = G_ONCE_INIT;
  g_once (&my_once, (GThreadFunc) _init_xmp_tag_map, NULL);
}
