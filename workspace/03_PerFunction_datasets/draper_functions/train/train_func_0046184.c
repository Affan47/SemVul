connect (const char* host)
{
  if (pn == protocol::nil) throw sockerr (EPROTONOSUPPORT);
  sockinetbuf::connect (host, rfc_name (), protocol_name ());
}
