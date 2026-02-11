onTimeoutInterval()
{
  int count = 0;
  for ( size_t i = 0; i < _dataSockets.size();++i )
  {
    if ( _dataSockets[i]->bytesRead() > 0 ) onData ( _dataSockets[i] );
    dmtcp::vector<char>& buffer = _drainedData[_dataSockets[i]->socket().sockfd() ];
    if ( buffer.size() >= sizeof ( theMagicDrainCookie )
	 && memcmp ( &buffer[buffer.size() - sizeof ( theMagicDrainCookie ) ]
                     , theMagicDrainCookie
                     , sizeof ( theMagicDrainCookie ) ) == 0 )
    {
      buffer.resize ( buffer.size() - sizeof ( theMagicDrainCookie ) );
      JTRACE ( "buffer drain complete" ) ( _dataSockets[i]->socket().sockfd() ) ( buffer.size() ) ( ( _dataSockets.size() ) );
      _dataSockets[i]->socket() = -1;
    }
    else
      ++count;
  }

  if ( count == 0 )
  {
    _listenSockets.clear();
  }else{
    const static int WARN_INTERVAL_TICKS = (int)(DRAINER_WARNING_FREQ/DRAINER_CHECK_FREQ + 0.5);
    const static float WARN_INTERVAL_SEC = WARN_INTERVAL_TICKS*DRAINER_CHECK_FREQ;
    if(_timeoutCount++ > WARN_INTERVAL_TICKS){
      _timeoutCount=0;
      for ( size_t i = 0; i < _dataSockets.size();++i ){
        dmtcp::vector<char>& buffer = _drainedData[_dataSockets[i]->socket().sockfd() ];
        JWARNING(false)(_dataSockets[i]->socket().sockfd())(buffer.size())(WARN_INTERVAL_SEC)
                 .Text("Still draining socket... perhaps remote host is not running under DMTCP?");
#ifdef CERN_CMS
        JNOTE("\n*** Closing this socket (to database?? ).  Please use dmtcpaware to\n"
              "***  gracefully handle database connections, and re-run.\n"
              "***  Trying a workaround for now, and hoping it doesn't fail.\n");
        _real_close(_dataSockets[i]->socket().sockfd());

	int sp[2] = {-1,-1};
	JASSERT ( _real_socketpair ( AF_UNIX, SOCK_STREAM, 0, sp ) == 0 ) ( JASSERT_ERRNO )
		.Text ( "socketpair() failed" );
	JASSERT ( sp[0]>=0 && sp[1]>=0 ) ( sp[0] ) ( sp[1] )
		.Text ( "socketpair() failed" );
	_real_close ( sp[1] );
	JTRACE ( "created dead socket" ) ( sp[0] );
	_real_dup2(sp[0], _dataSockets[i]->socket().sockfd());
#endif

      }
    }
  }
}
