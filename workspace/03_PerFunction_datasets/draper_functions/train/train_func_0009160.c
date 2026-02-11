changeFd ( int newFd )
{
  if ( _sockfd == newFd ) return;
  JASSERT ( newFd == dup2 ( _sockfd, newFd ) )
      ( _sockfd ) ( newFd ).Text ( "dup2 failed" );
  close();
  _sockfd = newFd;
}
