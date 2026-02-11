_wnck_get_session_id (Screen *screen,
                      Window  xwindow)
{
  Window client_leader;

  client_leader = None;
  _wnck_get_window (screen, xwindow,
                    _wnck_atom_get ("WM_CLIENT_LEADER"),
                    &client_leader);

  if (client_leader == None)
    return NULL;

  return _wnck_get_string_property_latin1 (screen, client_leader,
                                           _wnck_atom_get ("SM_CLIENT_ID"));
}
