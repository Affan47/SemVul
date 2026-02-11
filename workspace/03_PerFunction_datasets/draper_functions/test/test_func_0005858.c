GWEN_Gui_Internal_ShowBox(GWEN_GUI *gui,
				   uint32_t flags,
				   const char *title,
				   const char *text,
				   uint32_t guiid) {
  GWEN_DIALOG *dlg;
  int rv;
  uint32_t id;

  id=++(gui->nextDialogId);

  dlg=GWEN_DlgShowBox_new(flags, title, text);
  if (dlg==NULL) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not create dialog");
    return 0;
  }

  GWEN_Dialog_SetGuiId(dlg, id);

  rv=GWEN_Gui_OpenDialog(dlg, guiid);
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    GWEN_Dialog_free(dlg);
    return 0;
  }

  GWEN_Dialog_List_Add(dlg, gui->activeDialogs);

  return id;
}
