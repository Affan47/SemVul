writeRecHook_BeginCollOp( HooksC::VaArgsT & args )
{
   bool error = false;


   if( !Params.createsnaps )
      return ;


   OTF_WStream **      wstream  = (OTF_WStream**)args[0];
   uint64_t *          time     = (uint64_t*)args[1];
   uint32_t *          proc     = (uint32_t*)args[2];
   uint32_t *          op       = (uint32_t*)args[3];
   uint64_t *          matchid  = (uint64_t*)args[4];
   uint32_t *          comm     = (uint32_t*)args[5];
   uint32_t *          root     = (uint32_t*)args[6];
   uint64_t *          sent     = (uint64_t*)args[7];
   uint64_t *          recvd    = (uint64_t*)args[8];
   uint32_t *          scl      = (uint32_t*)args[9];
   OTF_KeyValueList ** kvs      = (OTF_KeyValueList**)args[10];
   bool *              do_write = (bool*)args[11];


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


   if( !error && *do_write )
   {
      OTF_KeyValueList * snapshot_kvs = 0;
      if( OTF_KeyValueList_getCount( *kvs ) > 0 )
      {


         snapshot_kvs = OTF_KeyValueList_clone( *kvs );
         vt_assert( snapshot_kvs );
      }

      int auxret =
         OTFAUX_State_processBeginCollectiveOperation( stream_context->auxstate,
            *time, *proc, *comm, *root, *op, *matchid, *sent, *recvd,
            *scl, snapshot_kvs );
      vt_assert( auxret );
   }


   vt_assert( !error );
}
