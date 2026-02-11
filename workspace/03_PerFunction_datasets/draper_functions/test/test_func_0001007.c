HandleAnonTLSAuth(rfbClient* client)
{
  if (!InitializeTLS() || !InitializeTLSSession(client, TRUE)) return FALSE;

  if (!SetTLSAnonCredential(client)) return FALSE;

  if (!HandshakeTLS(client)) return FALSE;

  return TRUE;
}
