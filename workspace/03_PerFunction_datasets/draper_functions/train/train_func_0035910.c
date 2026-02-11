is_legacy(cnu user)
{
  cnr room;

  if(user == NULL)
  {
    log_warn(NAME, "[%s] ERR: Missing variable in is_legacy", FZONE);
    return 0;
  }

  room = user->room;

  if(room->legacy)
    return 1;
  else if(user->legacy)
    return 1;
  else
    return 0;
}
