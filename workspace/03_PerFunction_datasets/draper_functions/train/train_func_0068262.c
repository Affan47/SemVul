bSaveFile( const wxString & rosFName )
{

  if( ! NetList::bSaveFile( rosFName ) ) return( FALSE );


  if( ! bSaveSigSrc( ) )                 return( FALSE );

  return( TRUE );
}
