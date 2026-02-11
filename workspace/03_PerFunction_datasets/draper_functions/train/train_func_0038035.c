main(int argc, char **argv)
{
  register_imagelib(appimglib_imagelib);
  init_ace(argc, argv, fmap);
  splash = get_picture("spider");
  youwin = get_picture("youwin");
  youlose = get_picture("youlose");
  arrow = get_picture("golf-arrow");
  no_arrow = get_picture("golf-noarrow");
  if (table_width == 0 || table_height == 0)
    {
      table_width = 10*(W+M) + M;
      table_height = 600;
    }
  init_table(table_width, table_height);
  table_loop();
  return 0;
}
