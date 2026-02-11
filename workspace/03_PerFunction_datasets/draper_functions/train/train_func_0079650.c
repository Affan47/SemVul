processNetDev( void )
{
  int i;

  if ( NetDevCnt == 0 )
		return;

  for ( i = 0; i < 5 && processNetDev_() < 0; ++i ) {


      exitNetDev();
      initNetDev( NetDevSM );
  }


  if ( i == 5 )
    exitNetDev();
}
