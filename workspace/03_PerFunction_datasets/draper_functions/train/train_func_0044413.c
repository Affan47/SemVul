AB_NewAccountDialog_new(AB_BANKING *ab, const char *dname) {
  GWEN_DIALOG *dlg;
  AB_NEWACCOUNT_DIALOG *xdlg;

  dlg=GWEN_Dialog_new(dname);
  GWEN_NEW_OBJECT(AB_NEWACCOUNT_DIALOG, xdlg);
  GWEN_INHERIT_SETDATA(GWEN_DIALOG, AB_NEWACCOUNT_DIALOG, dlg, xdlg,
		       AB_NewAccountDialog_FreeData);

  return dlg;
}
