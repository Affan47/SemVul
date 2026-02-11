Check( void ) {
  bool rc = CheckTrigger();

  if ( rc ) {
    TLWList deps;
    deps.AddHead( new TLWNode( "", this, ID() ) );

    rc = CheckDependencies( deps );
  }
  return rc;
}
