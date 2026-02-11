readLocal()
{
   bool error = false;

   VPrint( 2, " Reading local markers\n" );


   LargeVectorC<DefRec_DefMarkerS*> loc_defs;


   LargeVectorC<MarkerSpotS*> loc_spots;

   do
   {

      for( uint32_t i = 0; i < MyStreamIds.size(); i++ )
      {
         const uint32_t & streamid = MyStreamIds[i];


         if( (error = !readLocal( streamid, loc_defs, loc_spots )) )
            break;
      }
      if( SyncError( &error ) )
         break;


#ifdef VT_MPI
      if( NumRanks > 1 )
      {


         error = !gatherLocal( GATHER_TYPE_DEFS, &loc_defs );


         SLAVE
         {
            for( uint32_t i = 0; i < loc_defs.size(); i++ )
               delete loc_defs[i];
            loc_defs.clear();
         }
      }
#endif

      MASTER
      {


         for( uint32_t i = 0; i < loc_defs.size(); i++ )
         {

            m_tkfacScope->create( loc_defs[i] );

            delete loc_defs[i];
         }

         loc_defs.clear();
      }


#ifdef VT_MPI
      if( NumRanks > 1 )
      {


         error = !gatherLocal( GATHER_TYPE_SPOTS, &loc_spots );
         if( SyncError( &error ) )
            break;


         SLAVE
         {
            for( uint32_t i = 0; i < loc_spots.size(); i++ )
               delete loc_spots[i];
            loc_spots.clear();
         }
      }
#endif

      MASTER
      {


         for( uint32_t i = 0; i < loc_spots.size(); i++ )
         {
            MarkerSpotS new_glob_spot = *(loc_spots[i]);


            new_glob_spot.time =
               theTimeSync->correctTime( new_glob_spot.proc,
                  new_glob_spot.time );


            new_glob_spot.marker =
               m_tkfacScope->translate
                  ( new_glob_spot.proc, new_glob_spot.marker );
            vt_assert( new_glob_spot.marker != 0 );


            m_globSpots.push_back( new_glob_spot );


            delete loc_spots[i];
         }

         loc_spots.clear();


         std::stable_sort( m_globSpots.begin(), m_globSpots.end(),
                           std::less<MarkerSpotS>() );
      }

   } while( false );

   return !error;
}
