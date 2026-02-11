refresh_title_window(void)
{
  char szPackageTitle[STRING_LENGTH];
  char* szSite = N_("http://cunit.sourceforge.net/");
  static bool bFirstTime = true;

  if (!bFirstTime) {
    bFirstTime = false;
    return;
  }

  snprintf(szPackageTitle, STRING_LENGTH,
           "%s%s", _("CUnit - A Unit testing framework for C - Version "), CU_VERSION);
  wattrset(application_windows.pTitleWin, A_BOLD | COLOR_PAIR(TITLE_COLOR));
  mvwprintw(application_windows.pTitleWin,
            0, f_nLeft + (f_nWidth - strlen(szPackageTitle))/2,
            "%s", szPackageTitle);

  wattrset(application_windows.pTitleWin, A_BOLD | A_UNDERLINE | COLOR_PAIR(TITLE_COLOR));
  mvwprintw(application_windows.pTitleWin, 1, f_nLeft + (f_nWidth - strlen(_(szSite)))/2,
            "%s", _(szSite));
  wattrset(application_windows.pTitleWin, A_NORMAL);

  wrefresh(application_windows.pTitleWin);
}
