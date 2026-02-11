findPeer (const char *name)
{
  value *v = NULL ;
  int i ;

  for (i = 0 ; i < peerTableIdx ; i++)
    if (strcmp (peerTable[i].peerName,name) == 0)
      {
        v = peerTable[i].peerValue ;
        break ;
      }

  return v ;
}
