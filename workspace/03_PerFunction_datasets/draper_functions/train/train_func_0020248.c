initialize_local (u_short port_number)
{
  ACE_TCHAR name[MAXHOSTNAMELEN + 1];
  if (ACE_OS::hostname (name, MAXHOSTNAMELEN+1) == -1)
    return -1;

  this->external_.set (port_number, name);
  this->internal_.set (port_number, ACE_TEXT ("localhost"));
  return 0;
}
