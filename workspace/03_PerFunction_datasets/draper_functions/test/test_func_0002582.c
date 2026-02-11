tracklist_set(int pos, bool focus)
{

  sess_search_t *s = g_session.search;
  for (int i = 0; s && i != pos; ++i, s = s->next);

  if (g_res != s->res) {
    g_res = s->res;
    g_pos = 0;
  }

  if (focus)
    ui_focus(UI_TRACKLIST);
  else
    ui_dirty(UI_TRACKLIST);

  event_msg_post(MSG_CLASS_APP, MSG_APP_UPDATE, NULL);
}
