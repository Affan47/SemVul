horiz_taxrate_callback(struct widget *pHoriz_Src)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    struct rates_move pMotion;

    pMotion.pHoriz_Src = pHoriz_Src;
    pMotion.pLabel_Src = pHoriz_Src->prev;

    switch (pHoriz_Src->ID) {
      case ID_CHANGE_TAXRATE_DLG_LUX_SCROLLBAR:
        if (SDL_Client_Flags & CF_CHANGE_TAXRATE_LUX_BLOCK) {
          goto END;
        }
        pMotion.src_rate = (int *)pHoriz_Src->data.ptr;
        pMotion.pHoriz_Dst = pHoriz_Src->prev->prev->prev;
        pMotion.dst_rate = (int *)pMotion.pHoriz_Dst->data.ptr;
        pMotion.tax = 100 - *pMotion.src_rate - *pMotion.dst_rate;
        if ((SDL_Client_Flags & CF_CHANGE_TAXRATE_SCI_BLOCK)) {
          if (pMotion.tax <= get_player_bonus(client.conn.playing, EFT_MAX_RATES)) {
            pMotion.pHoriz_Dst = NULL;
            pMotion.dst_rate = &pMotion.tax;
          } else {
            goto END;
          }
        }

      break;

      case ID_CHANGE_TAXRATE_DLG_SCI_SCROLLBAR:
        if ((SDL_Client_Flags & CF_CHANGE_TAXRATE_SCI_BLOCK)) {
          goto END;
        }
        pMotion.src_rate = (int *)pHoriz_Src->data.ptr;
        pMotion.pHoriz_Dst = pHoriz_Src->next->next->next;
        pMotion.dst_rate = (int *)pMotion.pHoriz_Dst->data.ptr;
        pMotion.tax = 100 - *pMotion.src_rate - *pMotion.dst_rate;
        if (SDL_Client_Flags & CF_CHANGE_TAXRATE_LUX_BLOCK) {
          if (pMotion.tax <= get_player_bonus(client.conn.playing, EFT_MAX_RATES)) {

            pMotion.pHoriz_Dst = NULL;
            pMotion.dst_rate = &pMotion.tax;
          } else {
            goto END;
          }
        }

      break;

      default:
        return -1;
    }

    if(pMotion.pHoriz_Dst) {
      pMotion.pLabel_Dst = pMotion.pHoriz_Dst->prev;
    } else {

      pMotion.pLabel_Dst = pEconomyDlg->pEndWidgetList->prev->prev;
    }

    pMotion.min = pHoriz_Src->next->size.x + pHoriz_Src->next->size.w + adj_size(2);
    pMotion.gov_max = get_player_bonus(client.conn.playing, EFT_MAX_RATES);
    pMotion.max = pMotion.min + pMotion.gov_max * 1.5;
    pMotion.x = pHoriz_Src->size.x;

    MOVE_STEP_Y = 0;

    SDL_SetEventFilter(FilterMouseMotionEvents);
    gui_event_loop((void *)(&pMotion), NULL, NULL, NULL, NULL,
                    report_scroll_mouse_button_up,
                          report_scroll_mouse_motion_handler);

    SDL_SetEventFilter(NULL);
    MOVE_STEP_Y = DEFAULT_MOVE_STEP;

END:
    unsellect_widget_action();
    pSellected_Widget = pHoriz_Src;
    set_wstate(pHoriz_Src, FC_WS_SELLECTED);
    widget_redraw(pHoriz_Src);
    widget_flush(pHoriz_Src);
  }
  return -1;
}
