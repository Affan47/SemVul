isSessionLeader(){
      JTRACE("")(_virtualPidTable.sid()) (upid().pid());
      if( _virtualPidTable.sid() == upid().pid() )
	return true;
      else
	return false;
    }
