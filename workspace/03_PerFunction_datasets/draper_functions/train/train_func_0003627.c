printcap ( char *s , cap c )
{
  int i ;
  msg ( "N-+ %s" , s ) ;
  checkcap ( c ) ;
  for ( i=0 ; i<NCAP ; i++ )
    msg ( "N-+  %s" , capvaluestr [ i ] [ c[i] ] ) ;
  msg ( "N-" ) ;
}
