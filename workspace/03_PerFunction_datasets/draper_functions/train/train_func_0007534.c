writeRecHook_RecvMsg( HooksC::VaArgsT & args )
{
   bool error = false;


   OTF_WStream **      wstream  = (OTF_WStream**)args[0];
   uint64_t *          time     = (uint64_t*)args[1];
   uint32_t *          receiver = (uint32_t*)args[2];


   bool *              do_write = (bool*)args[9];


   static StreamContextS * stream_context = 0;
#if defined(HAVE_OMP) && HAVE_OMP
#  pragma omp threadprivate(stream_context)
#endif
   if( !stream_context || stream_context->streamid != *receiver )
   {
      stream_context = getStreamContext( *receiver );
      vt_assert( stream_context );
   }


   if( Params.createsnaps )
      error = !writeSnapshots( stream_context, *time, *wstream );


   if( !error && *do_write && Params.domsgmatch && Params.droprecvs )
      *do_write = false;


   vt_assert( !error );
}
