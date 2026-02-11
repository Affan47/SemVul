sendNextCommand(CliConn *conn)  {
  const char  *crPos;
  int  sendLen;
  Str  temp;

  assert(conn->server == cliServer_igs);
  assert(conn->promptReady);
  if (str_len(&conn->outMsgs))  {
    crPos = strchr(str_chars(&conn->outMsgs), '\n');
    assert(crPos != NULL);
    sendLen = (crPos - str_chars(&conn->outMsgs)) + 1;
    transmitData(conn, str_chars(&conn->outMsgs), sendLen);
    if (sendLen == str_len(&conn->outMsgs))  {
      str_clip(&conn->outMsgs, 0);
    } else  {
      str_initStr(&temp, &conn->outMsgs);
      str_copyCharsLen(&conn->outMsgs,
		       str_chars(&temp) + sendLen, str_len(&temp) - sendLen);
      str_deinit(&temp);
    }
    conn->promptReady = FALSE;
  }
}
