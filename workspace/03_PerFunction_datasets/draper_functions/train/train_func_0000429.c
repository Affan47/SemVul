AO_EditUserDialog_HandleActivated(GWEN_DIALOG *dlg, const char *sender) {
  DBG_ERROR(0, "Activated: %s", sender);
  if (strcasecmp(sender, "abortButton")==0) {
    return GWEN_DialogEvent_ResultReject;
  }
  else if (strcasecmp(sender, "okButton")==0) {
    int rv;

    rv=AO_EditUserDialog_GetBankPageData(dlg);
    if (rv<0) {
      DBG_INFO(AQOFXCONNECT_LOGDOMAIN, "here (%d)", rv);
      return GWEN_DialogEvent_ResultHandled;
    }

    rv=AO_EditUserDialog_GetUserPageData(dlg);
    if (rv<0) {
      DBG_INFO(AQOFXCONNECT_LOGDOMAIN, "here (%d)", rv);
      return GWEN_DialogEvent_ResultHandled;
    }

    rv=AO_EditUserDialog_GetAppPageData(dlg);
    if (rv<0) {
      DBG_INFO(AQOFXCONNECT_LOGDOMAIN, "here (%d)", rv);
      return GWEN_DialogEvent_ResultHandled;
    }

    rv=AO_EditUserDialog_FromGui(dlg);
    if (rv<0) {
      DBG_INFO(AQOFXCONNECT_LOGDOMAIN, "here (%d)", rv);
      return GWEN_DialogEvent_ResultHandled;
    }
    return GWEN_DialogEvent_ResultAccept;
  }
  else if (strcasecmp(sender, "wiz_bank_button")==0)
    return AO_EditUserDialog_HandleActivatedBankSelect(dlg);
  else if (strcasecmp(sender, "wiz_app_combo")==0)
    return AO_EditUserDialog_HandleActivatedApp(dlg);
  else if (strcasecmp(sender, "wiz_special_button")==0)
    return AO_EditUserDialog_HandleActivatedSpecial(dlg);
  else if (strcasecmp(sender, "wiz_getaccounts_button")==0)
    return AO_EditUserDialog_HandleActivatedGetAccounts(dlg);
  else if (strcasecmp(sender, "wiz_help_button")==0) {

  }

  return GWEN_DialogEvent_ResultNotHandled;
}
