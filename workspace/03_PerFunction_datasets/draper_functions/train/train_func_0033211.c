remove_preset(Widget w, XtPointer list,
                          XtPointer call_data)
{
  XawListReturnStruct *ret = XawListShowCurrent(preset_list);
  char buf[256];

  if (ret->list_index != XAW_LIST_NONE && cmafec_preset_num()) {
    fc_snprintf(buf, sizeof(buf),
                _("Do you really want to remove %s?"),
                cmafec_preset_get_descr(ret->list_index));

    popup_message_dialog(cma_dialog, "cmaremovepreset",
                         buf, remove_preset_yes,
                         INT_TO_XTPOINTER(ret->list_index), 0,
                         remove_preset_no, 0, 0,
                         NULL);
  }
}
