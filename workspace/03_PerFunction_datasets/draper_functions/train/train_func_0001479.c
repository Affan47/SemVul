con_send_alert(cnu user, char *text, char *subject, const char *status)
{
  xmlnode msg = _con_send_alert(user, text, subject, status,0);

  if(msg)
  {
    deliver(dpacket_new(msg), NULL);
  }
}
