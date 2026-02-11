test_board_end(gpointer data) {
   GList *full_list = (GList *) data;
   gc_close_all_dialog();

  gc_board_stop();
  if (full_list->next) {
    full_list = full_list->next;
    g_timeout_add(600, test_board_start, full_list);
  } else {
    printf("TEST DONE\n");
  }
  return FALSE;
}
