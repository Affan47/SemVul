footer_draw(ui_t *ui)
{

  if (g_input.type == INPUT_NONE) {
    switch (g_session.state) {
      case SESS_OFFLINE:
        mvwprintw(ui->win, 0, 0, "OFFLINE");
        break;

      case SESS_ONLINE:
        mvwprintw(ui->win, 0, 0, "ONLINE %s", g_session.dsfy->user_info->server_host);
        break;

      case SESS_ERROR:
         mvwprintw(ui->win, 0, 0, "ERROR (see log for details)");
        break;
    }
  }

  else {
    wchar_t *wbuf;

    unsigned int curx = strlen(g_titles[g_input.type]) + 2;

    unsigned int avail = DSFY_MAX(ui->width - curx - 1, 0);

    unsigned int offset = g_input.pos > avail ? g_input.pos - avail : 0;


    if (g_input.type == INPUT_PASSWORD) {
      wbuf = L"";
    }
    else  {
      wbuf = g_input.wbuf;
      curx = DSFY_MIN(curx + g_input.pos, curx + avail);
    }

    wchar_t str[ui->width];
    swprintf(str, sizeof(str), L"%s> %.*ls", g_titles[g_input.type], avail, wbuf + offset);
    mvwaddwstr(ui->win, 0, 0, str);


    mvwchgat(ui->win, 0, curx, 1, A_REVERSE, UI_STYLE_NORMAL, NULL);
  }
}
