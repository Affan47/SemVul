FuncCLOSE_PTY_IOSTREAM( Obj self, Obj stream )
{
  UInt pty = INT_INTOBJ(stream);
  int status;
  int retcode;

  while (!PtyIOStreams[pty].inuse)
    pty = INT_INTOBJ(ErrorReturnObj("IOSTREAM %d is not in use",pty,0L,
                                    "you can replace stream number <num> via 'return <num>;'"));

  PtyIOStreams[pty].inuse = 0;


  retcode = close(PtyIOStreams[pty].ptyFD);
  if (retcode)
    Pr("Strange close return code %d\n",retcode, 0);
  kill(PtyIOStreams[pty].childPID, SIGTERM);
  retcode = waitpid(PtyIOStreams[pty].childPID, &status, 0);
  FreeStream(pty);
  return 0;
}
