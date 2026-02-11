IDirectFBVideoProvider_CreateFromBuffer( IDirectFBDataBuffer     *buffer,
                                         CoreDFB                 *core,
                                         IDirectFBVideoProvider **interface )
{
     DFBResult                            ret;
     DirectInterfaceFuncs                *funcs = NULL;
     IDirectFBDataBuffer_data            *buffer_data;
     IDirectFBVideoProvider              *videoprovider;
     IDirectFBVideoProvider_ProbeContext  ctx;


     buffer_data = (IDirectFBDataBuffer_data*) buffer->priv;
     if (!buffer_data)
          return DFB_DEAD;


     ctx.filename = buffer_data->filename;
     ctx.buffer   = buffer;


     ret = buffer->WaitForData( buffer, sizeof(ctx.header) );
     if (ret)
          return ret;


     memset( ctx.header, 0, sizeof(ctx.header) );


     buffer->PeekData( buffer, sizeof(ctx.header), 0, ctx.header, NULL );


     ret = DirectGetInterface( &funcs, "IDirectFBVideoProvider", NULL, DirectProbeInterface, &ctx );
     if (ret)
          return ret;

     DIRECT_ALLOCATE_INTERFACE( videoprovider, IDirectFBVideoProvider );


     IDirectFBVideoProvider_Construct( videoprovider );


     ret = funcs->Construct( videoprovider, buffer, core );
     if (ret)
          return ret;

     *interface = videoprovider;

     return DFB_OK;
}
