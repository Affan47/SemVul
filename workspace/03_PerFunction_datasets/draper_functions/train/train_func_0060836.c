IDirectFBDataBuffer_CreateImageProvider( IDirectFBDataBuffer     *thiz,
                                         IDirectFBImageProvider **interface )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBDataBuffer)


     if (!interface)
          return DFB_INVARG;

     return IDirectFBImageProvider_CreateFromBuffer( thiz, data->core, interface );
}
