bSetPosn( long liPosn )
{
  TextCtrl * poTxtCtl;


  if( ! bIsCreated( ) )  return( FALSE );


  poTxtCtl = (TextCtrl *) GetCurrentPage( );

  if( poTxtCtl == NULL ) return( FALSE );


  if( liPosn >= 0 ) poTxtCtl->SetInsertionPoint( liPosn );
  else              poTxtCtl->SetInsertionPointEnd( );

  return( TRUE );
}
