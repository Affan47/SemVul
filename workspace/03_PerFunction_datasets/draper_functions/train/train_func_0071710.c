init_xml(guint level)
{
  gchar *filename;

  if(board_list)
    {
      missing_destroy_board_list(board_list);
      board_list = NULL;
    }
  filename = gc_file_find_absolute("%s/board%d.xml",
				   gcomprisBoard_missing->boarddir,
				   level);
  missing_read_xml_file(filename, &board_list);
  gcomprisBoard_missing->number_of_sublevel = g_list_length(board_list);
  g_free(filename);
}
