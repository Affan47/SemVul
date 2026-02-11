getState( int player )
{
   if( !gamemap->getField ( pos ) ) {
      displaymessage ("invalid event - map field not found!", 1);
      return finally_fulfilled;
   }

   MapField* fld = gamemap->getField ( pos );
   if ( !fld->building )
      return finally_fulfilled;
   else
      return unfulfilled;
}
