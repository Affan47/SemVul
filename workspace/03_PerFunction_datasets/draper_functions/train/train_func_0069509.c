startCoordinatorIfNeeded(int modes,
                                                          int isRestart)
{
  const static int CS_OK = DMTCP_FAIL_RC+1;
  const static int CS_NO = DMTCP_FAIL_RC+2;
  int coordinatorStatus = -1;

  if (modes & COORD_BATCH) {
    startNewCoordinator ( modes, isRestart );
    return;
  }

  if (fork()==0) {

    dup2(2,1);
    dup2(open("/dev/null",O_RDWR), 2);
    int result[DMTCPMESSAGE_NUM_PARAMS];
    DmtcpCoordinatorAPI coordinatorAPI;
    {
      if ( coordinatorAPI.tryConnectToCoordinator() == false ) {
        JTRACE("Coordinator not found.  Will try to start a new one.");
        _real_exit(DMTCP_FAIL_RC);
      }
    }

    coordinatorAPI.sendUserCommand('s',result);
    coordinatorAPI._coordinatorSocket.close();


    if(result[0]==0 || result[1] ^ isRestart){
      if(result[0] != 0) {
        int num_processes = result[0];
        JTRACE("Joining existing computation.") (num_processes);
      }
      _real_exit(CS_OK);
    }else{
      JTRACE("Existing computation not in a running state," \
	     " perhaps checkpoint in progress?");
      _real_exit(CS_NO);
    }
  }
  errno = 0;

  JASSERT(::wait(&coordinatorStatus)>0)(JASSERT_ERRNO);
  JASSERT(WIFEXITED(coordinatorStatus));


  if (WEXITSTATUS(coordinatorStatus) != CS_OK) {

    if(WEXITSTATUS(coordinatorStatus) == CS_NO){
      JASSERT (false) (isRestart)
	 .Text ("Coordinator in a funny state.  Peers exist, not restarting," \
		"\n but not in a running state.  Often this means you are" \
		" connecting to\n a stale coordinator from a previous" \
		" computation.\n Try killing the other coordinator," \
		" or using a different port for the new comp.");
    }else if (WEXITSTATUS(coordinatorStatus) == DMTCP_FAIL_RC) {
      JTRACE("Coordinator not found.  Starting a new one.");
    }else{
      JTRACE("Bad result found for coordinator.  Will try start a new one.");
    }

    startNewCoordinator ( modes, isRestart );

  }else{
    if (modes & COORD_FORCE_NEW) {
      JTRACE("Forcing new coordinator.  --new-coordinator flag given.");
      startNewCoordinator ( modes, isRestart );
      return;
    }
    JASSERT( modes & COORD_JOIN )
      .Text("Coordinator already running, but '--new' flag was given.");
  }
}
