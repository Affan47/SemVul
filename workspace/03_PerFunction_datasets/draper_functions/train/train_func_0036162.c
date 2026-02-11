worklist_avail_help_callback(Widget w, XtPointer client_data,
					  XtPointer call_data)
{
  struct worklist_dialog *pdialog;
  XawListReturnStruct *ret;
  struct universal production;

  pdialog=(struct worklist_dialog *)client_data;

  ret = XawListShowCurrent(pdialog->avail);
  if(ret->list_index!=XAW_LIST_NONE) {
    if (ret->list_index >= pdialog->worklist_avail_num_targets) {

      production.kind = VUT_NONE;
      production.value.building = NULL;
    } else {
      production =
        universal_by_number((ret->list_index >= pdialog->worklist_avail_num_improvements)
                               ? VUT_UTYPE : VUT_IMPROVEMENT,
                               pdialog->worklist_avail_ids[ret->list_index]);
    }
  } else {
    production.kind = VUT_NONE;
    production.value.building = NULL;
  }

  worklist_help(production);
}
