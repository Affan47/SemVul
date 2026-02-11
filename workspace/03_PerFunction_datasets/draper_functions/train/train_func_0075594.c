SetSizeHints( const wxArrayString & items )
{
   if( mShuttleMode != eIsCreating )
      return;

   SetSizeHints( mpLastWind, items );
}
