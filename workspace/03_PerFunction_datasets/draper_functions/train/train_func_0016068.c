GetValueString( void ) const {
  const char *ret = NULL;

  switch (event.GetData(0) ) {
  case 0:
  case 1:
    ret = mission.GetMessage(event.GetData(1));
    break;
  case 2:
    if ( event.GetTmpBuf() != "" ) ret = event.GetTmpBuf().c_str();
    break;
  }
  return ( ret == NULL ) ? "<None>" : ret;
}
