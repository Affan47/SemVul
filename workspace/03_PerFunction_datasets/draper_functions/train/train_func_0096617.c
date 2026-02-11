GWEN_Gui_Internal_HideBox(GWEN_GUI *gui, uint32_t id) {
  GWEN_DIALOG *dlg;

  if (id) {
    dlg=GWEN_Dialog_List_First(gui->activeDialogs);
    while(dlg) {
      if (GWEN_Dialog_GetGuiId(dlg)==id)
	break;
      dlg=GWEN_Dialog_List_Next(dlg);
    }
  }
  else
    dlg=GWEN_Dialog_List_Last(gui->activeDialogs);

  if (dlg) {
    int rv;

    rv=GWEN_Gui_CloseDialog(dlg);
    if (rv<0) {
      DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    }
    GWEN_Dialog_List_Del(dlg);
    GWEN_Dialog_free(dlg);
  }
}
