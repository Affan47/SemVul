exit_meta_severs_dlg_callback(struct widget *pWidget)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    queue_flush();

    server_scan_finish(pServer_scan);
    pServer_scan = NULL;
    pServer_list = NULL;

    set_client_page(PAGE_NETWORK);
    meswin_dialog_popup(TRUE);
  }
  return -1;
}
