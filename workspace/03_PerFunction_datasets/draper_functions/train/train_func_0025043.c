sidebar_keypress(wint_t ch, bool code)
{
  (void)code;

  if (!g_session.search_len)
    return ch;

  switch (ch) {
    case KEY_ENTER:
    case '\n':
    case '\r':
    case KEY_RIGHT:
    case 'l':
      tracklist_set(g_pos, true);
      break;

    case KEY_UP:
    case 'k':
      g_pos = DSFY_MAX((signed)g_pos - 1, 0);
      tracklist_set(g_pos, false);
      break;

    case KEY_DOWN:
    case 'j':
      g_pos = DSFY_MIN(g_pos + 1, g_session.search_len - 1);
      tracklist_set(g_pos, false);
      break;

    case KEY_HOME:
      g_pos = 0;
      tracklist_set(g_pos, false);
      break;

    case KEY_END:
      g_pos = g_session.search_len - 1;
      tracklist_set(g_pos, false);
      break;

    default:
      return ch;
  }

  ui_dirty(UI_SIDEBAR);
  event_msg_post(MSG_CLASS_APP, MSG_APP_UPDATE, NULL);

  return 0;
}
