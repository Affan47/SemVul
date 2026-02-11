genericHook( const uint32_t & id,
   HooksC::VaArgsT & args )
{
   bool error = false;


   if( !Params.createsnaps || !UnifyControlS::have_events() )
      return ;

   if( ( id & VT_UNIFY_HOOKS_MSGMATCH_SNAPS_GENID__DEF_WSTREAM_CLOSE ) != 0 )
   {

      OTF_WStream ** wstream = (OTF_WStream**)args[0];


      vt_assert( m_maxTime != (uint64_t)-1 );


      if( m_maxTime <= Params.maxsnapshots )
         m_snapshotInterval = 1;
      else
         m_snapshotInterval =
            (uint64_t)( ( (double)m_maxTime /
                          (double)( Params.maxsnapshots + 1 ) ) + 0.5 );


      for( uint64_t time = m_snapshotInterval; time <= m_maxTime;
           time += m_snapshotInterval )
      {


         error =
            ( OTF_WStream_writeDefAuxSamplePoint( *wstream, time,
#ifdef VT_UNIFY_HOOKS_MSGMATCH_SNAPS__INLINE_SNAPSHOTS
                 OTF_AUX_SAMPLE_POINT_INLINE_SNAPSHOT,
#else
                 OTF_AUX_SAMPLE_POINT_SNAPSHOT,
#endif
                 0 ) == 0 );
      }
   }
#ifdef VT_UNIFY_HOOKS_MSGMATCH_SNAPS__INLINE_SNAPSHOTS
   else if(
      ( id & VT_UNIFY_HOOKS_MSGMATCH_SNAPS_GENID__EVENT_WSTREAM_OPEN ) != 0 )
   {


      OTF_WStream ** wstream = (OTF_WStream**)args[0];


      OTF_WStream_setFormat( *wstream, OTF_WSTREAM_FORMAT_INLINE_SNAPSHOTS );
   }
#endif
   else if(
      ( id & VT_UNIFY_HOOKS_MSGMATCH_SNAPS_GENID__EVENT_WSTREAM_CLOSE ) != 0 )
   {


      OTF_WStream ** wstream = (OTF_WStream**)args[0];
      uint32_t * streamid = (uint32_t*)args[1];


      vt_assert( m_maxTime != (uint64_t)-1 );


      StreamContextS * stream_context = getStreamContext( *streamid );
      vt_assert( stream_context );


      error = !writeSnapshots( stream_context, m_maxTime, *wstream );
   }


   vt_assert( !error );
}
