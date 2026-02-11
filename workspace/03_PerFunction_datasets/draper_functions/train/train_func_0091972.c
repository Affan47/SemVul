onConnect ( const jalib::JSocket& sock,  const struct sockaddr* ,socklen_t  )
{
  jalib::JSocket remote = sock;
  DmtcpMessage msg;
  msg.poison();
  remote >> msg;
  msg.assertValid();
  JASSERT ( msg.type == DMT_RESTORE_RECONNECTED ) ( msg.type ).Text ( "unexpected message" );

  iterator i = _pendingIncoming.find ( msg.restorePid );

  JASSERT ( i != _pendingIncoming.end() ) ( msg.restorePid )
  .Text ( "got unexpected incoming restore request" );

  const dmtcp::vector<int>& fds = i->second;
  JASSERT ( fds.size() > 0 );
  int fd0 = fds[0];

  remote.changeFd ( fd0 );

  JTRACE ( "restoring incoming connection" ) ( msg.restorePid ) ( fd0 ) ( fds.size() );

  for ( size_t i = 1; i<fds.size(); ++i )
  {
    JTRACE ( "restoring extra fd" ) ( fd0 ) ( fds[i] );
    JASSERT ( _real_dup2 ( fd0,fds[i] ) == fds[i] ) ( fd0 ) ( fds[i] ) ( msg.restorePid )
    .Text ( "dup2() failed" );
  }

  _pendingIncoming.erase ( i );


  if ( pendingCount() ==0 ) finishup();
#ifdef DEBUG
  else debugPrint();
#endif
}
