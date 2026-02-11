activate_and_exit_units_orders_city_dlg_callback(struct widget *pButton)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    struct unit *pUnit = pButton->data.unit;

    if(pUnit) {

      popdown_window_group_dialog(pCityDlg->pBeginCityMenuWidgetList,
                                  pCityDlg->pEndCityMenuWidgetList);
      pCityDlg->pEndCityMenuWidgetList = NULL;

      popdown_city_dialog(pCityDlg->pCity);

      center_tile_mapcanvas(unit_tile(pUnit));
      unit_focus_set(pUnit);
    }
  }
  return -1;
}
