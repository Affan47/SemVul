resolution( const Cell& cell ) const
{
  if ( mode != READ )
    Message::message( Message_fatal( "CNS_HKLfile: resolution - no file open for read" ) );

  FILE* cns_hkl = fopen( filename.c_str(), "r" );
  if ( cns_hkl == NULL )
    Message::message( Message_fatal( "CNS_HKLfile: resolution - Could not read: "+filename ) );


  HKL hkl;
  ftype slim = 0.0;
  String s, t;
  while ( (s=cnstok(cns_hkl)).length() > 0 ) {
    t = (s+"   ").substr(0,4);
    if ( t == "INDE" ) {
      hkl.h() = cnstok(cns_hkl).i();
      hkl.k() = cnstok(cns_hkl).i();
      hkl.l() = cnstok(cns_hkl).i();
      slim = Util::max( slim, hkl.invresolsq(cell) );
    }
  }
  fclose( cns_hkl );

  return Resolution( 1.0/sqrt(slim) );
}
