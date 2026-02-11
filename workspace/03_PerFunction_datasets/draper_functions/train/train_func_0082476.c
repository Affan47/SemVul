cliConn_init(CliConn *cc, Cgoban *cg, int serverNum,
		       CliServer protocol,
		       uchar loChar, uchar hiChar,
		       void (*newData)(void *packet, const char *dataIn,
				      int dataLen),
		       void *packet)  {
  const char  *cliDirect;

  assert(MAGIC(cg));
  MAGIC_SET(cc);
  cc->cg = cg;
  cc->fd = -1;
  cc->inBuf = NULL;
  cc->outBuf = NULL;
  cc->err = cliConnErr_ok;
  cc->serverNum = serverNum;
  cc->server = protocol;
  cc->loginMode = TRUE;
  if (protocol == cliServer_igs)
    str_init(&cc->outMsgs);

  cliDirect = clp_getStrNum(cg->clp, "client.direct", serverNum);
  cc->directConn = (cliDirect[0] == 't');
  if (cc->directConn)  {
    sockConn(cc);
  } else  {
    assert(cliDirect[0] == 'f');
    progConn(cc);
  }
  if (cc->err != cliConnErr_ok)
    return(cc);

  fcntl(cc->fd, F_SETFL, O_NONBLOCK);
  butEnv_addFile(cg->env, BUT_READFILE, cc->fd, cc, newNetData);

  cc->inLen = 0;
  cc->telnetState = 0;
  cc->inBuf = wms_malloc(cc->inSize = defaultInLen);
  cc->outLen = 0;
  cc->outBuf = wms_malloc(cc->outSize = defaultOutLen);
  cc->promptReady = TRUE;
  if (loChar <= '\r')
    loChar = '\r' + 1;
  cc->loChar = loChar;
  cc->hiChar = hiChar;

  cc->newData = newData;
  cc->packet = packet;
  return(cc);
}
