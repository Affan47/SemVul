refresh_options_window(void)
{
  int nPos = 0;
  const char* szHotKey = NULL;

  wclear(application_windows.pOptionsWin);
  mvwprintw(application_windows.pOptionsWin, 0, 1, "%s", f_szOptions);

  get_hotkey(f_szOptions, NULL);
  wattron(application_windows.pOptionsWin, A_BOLD);
  while (NULL != (szHotKey = get_hotkey((const char*)NULL, &nPos))) {
    mvwaddstr(application_windows.pOptionsWin, 0, nPos + 1, szHotKey);
  }
  wattroff(application_windows.pOptionsWin, A_BOLD);

  wrefresh(application_windows.pOptionsWin);
}
