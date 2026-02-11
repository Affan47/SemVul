cliConn_send(CliConn *conn, const char *str)  {
#if  TRACELOG
  printf("***SEND  {\n%s***SEND  }\n", str);
#endif
  if ((conn->server == cliServer_nngs) || conn->loginMode)  {
    transmitData(conn, str, strlen(str));
  } else  {
    str_catChars(&conn->outMsgs, str);
    if (conn->promptReady)
      sendNextCommand(conn);
  }
}
