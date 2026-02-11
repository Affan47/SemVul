enable_city_dlg_widgets(void)
{
  if (pCityDlg) {
    set_group_state(pCityDlg->pBeginCityWidgetList,
		  pCityDlg->pEndCityWidgetList->prev, FC_WS_NORMAL);

    if (pCityDlg->pImprv->pEndActiveWidgetList) {

      if (pCityDlg->pImprv->pScroll) {
        set_wstate(pCityDlg->pImprv->pScroll->pScrollBar, FC_WS_NORMAL);
        set_wstate(pCityDlg->pImprv->pScroll->pUp_Left_Button, FC_WS_NORMAL);
        set_wstate(pCityDlg->pImprv->pScroll->pDown_Right_Button, FC_WS_NORMAL);
      }


      if (pCityDlg->pCity->did_sell
          || pCityDlg->pCity->owner != client.conn.playing) {
        set_group_state(pCityDlg->pImprv->pBeginActiveWidgetList,
		      pCityDlg->pImprv->pEndActiveWidgetList, FC_WS_DISABLED);
      } else {
        struct widget *pTmpWidget = pCityDlg->pImprv->pEndActiveWidgetList;

        while (TRUE) {
          struct impr_type *pimpr = improvement_by_number(MAX_ID - 3000 -
                                                          pTmpWidget->ID);

          if (!can_city_sell_building(pCityDlg->pCity, pimpr)) {
	    set_wstate(pTmpWidget, FC_WS_DISABLED);
	  } else {
	    set_wstate(pTmpWidget, FC_WS_NORMAL);
	  }

	  if (pTmpWidget == pCityDlg->pImprv->pBeginActiveWidgetList) {
	    break;
	  }

	  pTmpWidget = pTmpWidget->prev;

        }
      }
    }

    if (!city_can_buy(pCityDlg->pCity) && pCityDlg->pBuy_Button) {
      set_wstate(pCityDlg->pBuy_Button, FC_WS_DISABLED);
    }

    if (pCityDlg->pPanel) {
      set_group_state(pCityDlg->pPanel->pBeginWidgetList,
		    pCityDlg->pPanel->pEndWidgetList, FC_WS_NORMAL);
    }

    if (cma_is_city_under_agent(pCityDlg->pCity, NULL)) {
      set_wstate(pCityDlg->pResource_Map, FC_WS_DISABLED);
    }

    pCityDlg->lock = FALSE;
  }
}
