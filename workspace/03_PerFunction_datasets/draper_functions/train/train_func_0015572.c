end_turn_callback(struct widget *pButton)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    widget_redraw(pButton);
    widget_flush(pButton);
    disable_focus_animation();
    key_end_turn();
  }
  return -1;
}
