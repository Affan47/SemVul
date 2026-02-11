adv_unit_select_callback(struct widget *pWidget)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    struct unit *pUnit = pWidget->data.unit;

    popdown_advanced_terrain_dialog();

    if (pUnit) {
      request_new_unit_activity(pUnit, ACTIVITY_IDLE);
      unit_focus_set(pUnit);
    }
  }
  return -1;
}
