onBind (const struct sockaddr* addr, socklen_t len)
{
  if (really_verbose) {
    JTRACE ("Binding.") ( id() ) ( len );
  }
  JASSERT ( tcpType() == TCP_CREATED ) ( tcpType() ) ( id() )
    .Text ( "Binding a socket in use????" );
  JASSERT ( len <= sizeof _bindAddr ) ( len ) ( sizeof _bindAddr )
    .Text ( "That is one huge sockaddr buddy." );

  _type = TCP_BIND;
  _bindAddrlen = len;
  memcpy ( &_bindAddr, addr, len );
}
