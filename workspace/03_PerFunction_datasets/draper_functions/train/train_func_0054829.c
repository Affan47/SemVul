showResourceTable( const Resources& res ) {
         for ( int r = 0; r < 3; ++r ) {
            ASCString s = Resources::name(r);
            int amount = res.resource(r);
            if ( container()->maxplus.resource(r) < 0 ) {
               s += "In";
               amount  = -amount;
            } else {
               s += "Out";
            }
            if ( container()->maxplus.resource(r) != 0 )
               cargoDialog->setLabelText( s, amount, widget );
         }
      }
