run()
{
   bool error = false;

#ifdef VT_MPI

   if( NumRanks > 1 )
      CALL_MPI( MPI_Barrier( MPI_COMM_WORLD ) );
#endif

   if( m_scope == SCOPE_EVENTS )
   {
      VPrint( 1, "Unifying events\n" );


      theHooks->triggerPhaseHook( HooksC::Phase_UnifyEvents_pre );
   }
   else
   {
      VPrint( 1, "Unifying statistics\n" );


      theHooks->triggerPhaseHook( HooksC::Phase_UnifyStatistics_pre );
   }


   error = !rewrite();
   SyncError( &error );


   MASTER
   {
      if( error )
      {
         std::cerr << ExeName << ": "
                   << "An error occurred during unifying "
                   << ( m_scope == SCOPE_EVENTS ? "events. " : "statistics. " )
                   << "Aborting." << std::endl;
      }
   }


   if( !error )
   {
      theHooks->triggerPhaseHook( m_scope == SCOPE_EVENTS ?
         HooksC::Phase_UnifyEvents_post : HooksC::Phase_UnifyStatistics_post );
   }

   return !error;
}
