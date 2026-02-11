gc_selector_file_stop ()
{
  GcomprisBoard *gcomprisBoard = gc_board_get_current();

  if(gcomprisBoard!=NULL && file_selector_displayed)
    gc_board_pause(FALSE);


  if(rootitem!=NULL)
    goo_canvas_item_remove(rootitem);

  rootitem = NULL;


  file_root_item = NULL;

  gc_bar_hide(FALSE);
  file_selector_displayed = FALSE;


  current_extension = NULL;
}
