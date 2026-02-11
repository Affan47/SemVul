option_dialog_destroy(struct option_dialog *pdialog)
{
  fc_assert_ret(NULL != pdialog);

  if (ODM_OPTSET == pdialog->mode && -1 != pdialog->optset.category) {
    options_iterate(pdialog->optset.poptset, poption) {
      if (pdialog->optset.category == option_category(poption)) {
        option_set_gui_data(poption, NULL);
      }
    } options_iterate_end;
  }

  if (NULL != pdialog->advanced) {
    free(pdialog->advanced->pScroll);
    free(pdialog->advanced);
  }

  popdown_window_group_dialog(pdialog->begin_widget_list,
                              pdialog->end_widget_list);

  free(pdialog);
}
