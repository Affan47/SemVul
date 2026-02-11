initPin(char* keypwd, char* confirm) {
  PK11SlotInfo *slot= PK11_GetInternalKeySlot();
  char *tokenName = get_cgi_var("tokenname", NULL, NULL);

  if (tokenName != NULL) {
      slot= PK11_FindSlotByName(tokenName);
  }


  if (PORT_Strcmp(keypwd, confirm)) {
    errorRpt(INCORRECT_USAGE, getResourceString(DBT_INVALID_CONFIRM_PWD));
  }


  if (!slot || (PK11_InitPin(slot, 0,  keypwd) != SECSuccess)) {
    errorRpt(APP_ERROR, getResourceString(DBT_INIT_FAIL));
  }
}
