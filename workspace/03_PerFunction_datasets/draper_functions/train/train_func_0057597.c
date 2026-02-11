originalToCurrentPid( pid_t originalPid )
{ pid_t retVal = 0;


  _do_lock_tbl();
  pid_iterator i = _pidMapTable.find(originalPid);
  if ( i == _pidMapTable.end() ) {
    _do_unlock_tbl();
    return originalPid;
  }


  retVal = i->second;
  _do_unlock_tbl();
  return retVal;
}
