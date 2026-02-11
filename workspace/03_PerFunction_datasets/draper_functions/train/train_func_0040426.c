deleteMines( int player )
      {
         for ( int y = 0; y < gamemap->ysize; ++y )
            for ( int x = 0; x < gamemap->xsize; ++x ) {
               MapField* fld = gamemap->getField(x,y);
               for ( MapField::MineContainer::iterator i = fld->mines.begin(); i != fld->mines.end(); )
                  if ( i->player == player )
                     i = fld->mines.erase( i );
                  else
                     ++i;
            }

      }
