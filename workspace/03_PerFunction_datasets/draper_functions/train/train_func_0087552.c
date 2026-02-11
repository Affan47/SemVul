_matewnck_get_session_id (Window xwindow)
{
  Window client_leader;

  client_leader = None;
  _matewnck_get_window (xwindow,
                    _matewnck_atom_get ("WM_CLIENT_LEADER"),
                    &client_leader);

  if (client_leader == None)
    return NULL;

  return _matewnck_get_string_property_latin1 (client_leader,
                                           _matewnck_atom_get ("SM_CLIENT_ID"));
}
