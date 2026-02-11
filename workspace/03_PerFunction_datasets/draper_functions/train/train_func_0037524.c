AO_NewUserDialog_HandleValueChanged(GWEN_DIALOG *dlg, const char *sender) {
  if (strcasecmp(sender, "wiz_username_edit")==0 ||
      strcasecmp(sender, "wiz_userid_edit")==0 ||
      strcasecmp(sender, "wiz_url_edit")==0 ||
      strcasecmp(sender, "wiz_brokerid_edit")==0 ||
      strcasecmp(sender, "wiz_fid_edit")==0 ||
      strcasecmp(sender, "wiz_org_edit")==0 ||
      strcasecmp(sender, "wiz_appid_edit")==0 ||
      strcasecmp(sender, "wiz_appver_edit")==0 ||
      strcasecmp(sender, "wiz_headerver_edit")==0) {
    int rv;

    if (GWEN_Dialog_GetIntProperty(dlg, "wiz_stack", GWEN_DialogProperty_Value, 0, -1)==PAGE_BANK) {
      rv=AO_NewUserDialog_GetBankPageData(dlg);
      if (rv<0)
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 0, 0);
      else
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 1, 0);
    }
    else if (GWEN_Dialog_GetIntProperty(dlg, "wiz_stack", GWEN_DialogProperty_Value, 0, -1)==PAGE_USER) {
      rv=AO_NewUserDialog_GetUserPageData(dlg);
      if (rv<0)
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 0, 0);
      else
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 1, 0);
    }
    else if (GWEN_Dialog_GetIntProperty(dlg, "wiz_stack", GWEN_DialogProperty_Value, 0, -1)==PAGE_APP) {
      rv=AO_NewUserDialog_GetAppPageData(dlg);
      if (rv<0)
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 0, 0);
      else
	GWEN_Dialog_SetIntProperty(dlg, "wiz_next_button", GWEN_DialogProperty_Enabled, 0, 1, 0);
    }
    return GWEN_DialogEvent_ResultHandled;
  }
  return GWEN_DialogEvent_ResultNotHandled;
}
