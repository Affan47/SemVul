real_set_client_page(enum client_pages page)
{

  switch (page) {
  case PAGE_MAIN:

    gui_server_connect();
    break;
  case PAGE_GAME:
    if (old_page == PAGE_START) {
      popdown_start_page();
    }
    break;
  case PAGE_START:
    popup_start_page();
    conn_list_dialog_update();
    break;
  case PAGE_SCENARIO:
  case PAGE_LOAD:
  case PAGE_NETWORK:
  case PAGE_GGZ:
    break;
  }

  old_page = page;
}
