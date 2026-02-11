sell_imprvm_dlg_ok_callback(struct widget *pOK_Button)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    struct widget *pTmp = (struct widget *)pOK_Button->data.ptr;

    city_sell_improvement(pCityDlg->pCity, MAX_ID - 3000 - pTmp->ID);


    popdown_window_group_dialog(pCityDlg->pBeginCityMenuWidgetList,
                                pCityDlg->pEndCityMenuWidgetList);

    pCityDlg->pEndCityMenuWidgetList = NULL;


    del_widget_from_vertical_scroll_widget_list(pCityDlg->pImprv, pTmp);

    enable_city_dlg_widgets();

    if (pCityDlg->pImprv->pEndWidgetList) {
      set_group_state(pCityDlg->pImprv->pBeginActiveWidgetList,
                      pCityDlg->pImprv->pEndActiveWidgetList, FC_WS_DISABLED);
    }

    redraw_city_dialog(pCityDlg->pCity);
    flush_dirty();
  }
  return -1;
}
