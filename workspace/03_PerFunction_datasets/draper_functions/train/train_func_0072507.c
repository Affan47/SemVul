notify_goto_dialog_destroy(struct notify_goto_dialog *pdialog)
{
  widget_undraw(pdialog->window);
  widget_mark_dirty(pdialog->window);
  remove_gui_layer(pdialog->window->dst);

  del_widget_pointer_from_gui_list(pdialog->window);
  del_widget_pointer_from_gui_list(pdialog->close_button);
  if (NULL != pdialog->label) {
    del_widget_pointer_from_gui_list(pdialog->label);
  }

  notify_goto_list_destroy(pdialog->datas);
  free(pdialog);
}
