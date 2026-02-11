PrintPERange(
lListElem *ep,
int nm
) {
   dstring range_string = DSTRING_INIT;
   String str;

   DENTER(GUI_LAYER, "PrintPERange");

   range_list_print_to_string(lGetList(ep, nm), &range_string, true, false, false);
   str = XtNewString(sge_dstring_get_string(&range_string));
   sge_dstring_free(&range_string);

   DEXIT;
   return str;
}
