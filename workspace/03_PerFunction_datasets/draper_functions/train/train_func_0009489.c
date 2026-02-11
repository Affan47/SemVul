undoAction( const Context& context )
{
   MapField* fld = getMap()->getField(pos);
   if ( !fld )
      return ActionResult( 21002, pos );

   if ( layer < 0 )
      throw ActionResult( 21401 );

   if ( mineID > 0 ) {
      MapField::MineContainer::iterator i = fld->mines.begin();

      int l = layer;
      while ( l-- )
         ++i;

      MemoryStream memstream( mineBuffer, tnstream::reading );
      fld->mines.insert( i, Mine::newFromStream( memstream ));
   } else {
      MemoryStream memstream( mineBuffer, tnstream::reading );
      for ( int i = 0; i < layer; ++i )
         fld->mines.push_back( Mine::newFromStream( memstream ));
   }
   return ActionResult(0);
}
