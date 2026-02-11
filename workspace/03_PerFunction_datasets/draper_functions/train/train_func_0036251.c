ok()
      {
         if ( !properties->Apply() )
            return false;


         if ( ysize & 1 ) {
            warningMessage( "Height must be an even number!" );
            return false;
         }


         if ( create ) {
            TerrainType::Weather* w = terrainTypeRepository.getObject_byID( terrainid)->weather[0];
            if ( !w ) {
               warningMessage( "please choose a terrain!" );
               return false;
            }

            gamemap->allocateFields( xsize, ysize, w );

            if ( random)
               mapgenerator();

         }
         success = true;

         QuitModal();

         return true;
      }
