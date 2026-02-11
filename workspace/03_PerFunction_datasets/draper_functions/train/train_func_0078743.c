convert_portnr_callback(struct widget *pWidget)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    char pCharPort[6];
    char *tmp = convert_to_chars(pWidget->string16->text);

    if (tmp) {
      sscanf(tmp, "%d", &server_port);
      FC_FREE(tmp);
    } else {

      fc_snprintf(pCharPort, sizeof(pCharPort), "%d", server_port);
      copy_chars_to_string16(pWidget->string16, pCharPort);
      widget_redraw(pWidget);
      widget_mark_dirty(pWidget);
      flush_dirty();
    }
  }
  return -1;
}
