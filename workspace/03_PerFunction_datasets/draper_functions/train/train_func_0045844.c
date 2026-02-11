ok_save_cma_callback(struct widget *pWidget)
{
  if (Main.event.button.button == SDL_BUTTON_LEFT) {
    if(pWidget && pCma && pCma->pAdv) {
      struct widget *pEdit = (struct widget *)pWidget->data.ptr;
      char *name = convert_to_chars(pEdit->string16->text);

      if(name) {
        cmafec_preset_add(name, &pCma->edited_cm_parm);
        FC_FREE(name);
      } else {
        cmafec_preset_add(_("new preset"), &pCma->edited_cm_parm);
      }

      del_group_of_widgets_from_gui_list(pCma->pAdv->pBeginWidgetList,
                                                  pCma->pAdv->pEndWidgetList);
      FC_FREE(pCma->pAdv);

      update_city_cma_dialog();
    }
  }
  return -1;
}
