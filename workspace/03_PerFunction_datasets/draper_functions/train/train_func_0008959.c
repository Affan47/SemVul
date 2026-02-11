AB_EditUserDialog_HandleActivated(GWEN_DIALOG *dlg, const char *sender) {
  if (strcasecmp(sender, "bankCodeButton")==0)
    return AB_EditUserDialog_HandleActivatedBankCode(dlg);
  else if (strcasecmp(sender, "okButton")==0)
    return AB_EditUserDialog_HandleActivatedOk(dlg);
  else if (strcasecmp(sender, "abortButton")==0)
    return GWEN_DialogEvent_ResultReject;
  else if (strcasecmp(sender, "helpButton")==0) {

  }

  return GWEN_DialogEvent_ResultNotHandled;
}
