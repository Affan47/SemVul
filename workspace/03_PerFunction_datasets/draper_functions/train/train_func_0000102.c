operator+=( AbstractCommandPtr aCommand )
      throw( CommandFrameException )
   {
      GUARD;
      if( aCommand != NULLPTR )
      {
         theCommands.push_back( aCommand );
      }
      else
      {
         throw CommandFrameException( LOCATION );
      }

      return ( *this );
   }
