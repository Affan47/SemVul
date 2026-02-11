writeRecHook_EventComment( HooksC::VaArgsT & args )
{
   bool error = false;


   if( !Params.createsnaps )
      return ;


   OTF_WStream **      wstream  = (OTF_WStream**)args[0];
   uint64_t *          time     = (uint64_t*)args[1];
   uint32_t *          proc     = (uint32_t*)args[2];


   static StreamContextS * stream_context = 0;
#if defined(HAVE_OMP) && HAVE_OMP
#  pragma omp threadprivate(stream_context)
#endif
   if( !stream_context || stream_context->streamid != *proc )
   {
      stream_context = getStreamContext( *proc );
      vt_assert( stream_context );
   }


   error = !writeSnapshots( stream_context, *time, *wstream );


   vt_assert( !error );
}
