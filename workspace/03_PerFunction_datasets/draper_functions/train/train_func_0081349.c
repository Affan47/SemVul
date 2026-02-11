science_help_callback(Widget w, XtPointer client_data,
			    XtPointer call_data)
{
  XawListReturnStruct *ret=XawListShowCurrent(science_list);
  Boolean b;

  XtVaGetValues(science_help_toggle, XtNstate, &b, NULL);
  if (b == TRUE)
    {
      if(ret->list_index!=XAW_LIST_NONE)
	popup_help_dialog_typed(ret->string, HELP_TECH);
      else
	popup_help_dialog_string(HELP_TECHS_ITEM);
    }
}
