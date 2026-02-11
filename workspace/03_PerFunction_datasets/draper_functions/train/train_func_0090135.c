LD_cma_callback(struct widget *pWidget)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    bool load = pWidget->data.ptr != NULL;
    int index = MAX_ID - pWidget->ID;

    popdown_window_group_dialog(pCma->pAdv->pBeginWidgetList,
                                pCma->pAdv->pEndWidgetList);
    FC_FREE(pCma->pAdv->pScroll);
    FC_FREE(pCma->pAdv);

    if(load) {
      cm_copy_parameter(&pCma->edited_cm_parm, cmafec_preset_get_parameter(index));
      set_cma_hscrollbars();

      cmafec_set_fe_parameter(pCma->pCity, &pCma->edited_cm_parm);

      if (cma_is_city_under_agent(pCma->pCity, NULL)) {
        cma_release_city(pCma->pCity);
      }
    } else {
      cmafec_preset_remove(index);
    }

    update_city_cma_dialog();
  }
  return -1;
}
