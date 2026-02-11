isForegroundProcess() {
      JTRACE("")(_virtualPidTable.sid()) (upid().pid());
      if( _virtualPidTable.fgid() == _virtualPidTable.gid() )
	return true;
      else
	return false;
    }
