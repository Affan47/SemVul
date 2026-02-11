mergeWith ( const Connection& _that ){
  Connection::mergeWith(_that);
  const TcpConnection& that = (const TcpConnection&)_that;
  JWARNING(_sockDomain    == that._sockDomain)   MERGE_MISMATCH_TEXT;
  JWARNING(_sockType      == that._sockType)     MERGE_MISMATCH_TEXT;
  JWARNING(_sockProtocol  == that._sockProtocol) MERGE_MISMATCH_TEXT;
  JWARNING(_listenBacklog == that._listenBacklog)MERGE_MISMATCH_TEXT;
  JWARNING(_bindAddrlen   == that._bindAddrlen)  MERGE_MISMATCH_TEXT;


  JTRACE("Merging TcpConnections")(_acceptRemoteId)(that._acceptRemoteId);


  if(_acceptRemoteId.isNull())
    _acceptRemoteId = that._acceptRemoteId;

  if(!that._acceptRemoteId.isNull()){
    JASSERT(_acceptRemoteId == that._acceptRemoteId)(id())(_acceptRemoteId)(that._acceptRemoteId)
      .Text("Merging connections disagree on remote host");
  }
}
