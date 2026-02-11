rename_worklist_sub_callback(Widget w, XtPointer client_data,
				  XtPointer call_data)
{
  struct worklist_report_dialog *pdialog;

  pdialog = (struct worklist_report_dialog *)client_data;

  if (pdialog) {
      global_worklist_set_name(pdialog->worklist_ptr[pdialog->wl_idx],
                               input_dialog_get_input(w));
      update_worklist_report_dialog();
  }

  input_dialog_destroy(w);
}
