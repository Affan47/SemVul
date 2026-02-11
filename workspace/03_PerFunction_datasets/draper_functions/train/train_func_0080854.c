Construct( IDirectFBVideoProvider *thiz, ... )
{
     int fd;
     IDirectFBDataBuffer *buffer;
     IDirectFBDataBuffer_data *buffer_data;
     CoreDFB             *core;
     va_list              tag;

     DIRECT_ALLOCATE_INTERFACE_DATA(thiz, IDirectFBVideoProvider_V4L)

     va_start( tag, thiz );
     buffer = va_arg( tag, IDirectFBDataBuffer * );
     core = va_arg( tag, CoreDFB * );
     va_end( tag );


     data->ref  = 1;
     data->core = core;

     buffer_data = (IDirectFBDataBuffer_data*) buffer->priv;

     fd = open( buffer_data->filename, O_RDWR );
     if (fd < 0) {
          DFBResult ret = errno2result( errno );

          D_PERROR( "DirectFB/Video4Linux: Cannot open `%s'!\n",
                     buffer_data->filename );

          DIRECT_DEALLOCATE_INTERFACE( thiz );
          return ret;
     }

     direct_util_recursive_pthread_mutex_init( &data->lock );

#ifdef DFB_HAVE_V4L2
     data->is_v4l2 = 0;


     if (!ioctl( fd, VIDIOC_QUERYCAP, &data->caps )) {
          D_INFO( "DirectFB/Video4Linux: This is a Video4Linux-2 device.\n" );
          data->is_v4l2 = 1;
     }

     if (data->is_v4l2) {

     }
     else
#endif
     {
          D_INFO( "DirectFB/Video4Linux: This is a Video4Linux-1 device.\n" );

          ioctl( fd, VIDIOCGCAP, &data->vcap );
          ioctl( fd, VIDIOCCAPTURE, &zero );

          ioctl( fd, VIDIOCGMBUF, &data->vmbuf );

          data->buffer = mmap( NULL, data->vmbuf.size,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
     }

     data->filename = D_STRDUP( buffer_data->filename );
     data->fd       = fd;

     thiz->AddRef    = IDirectFBVideoProvider_V4L_AddRef;
     thiz->Release   = IDirectFBVideoProvider_V4L_Release;
     thiz->GetCapabilities = IDirectFBVideoProvider_V4L_GetCapabilities;
     thiz->GetSurfaceDescription = IDirectFBVideoProvider_V4L_GetSurfaceDescription;
     thiz->GetStreamDescription = IDirectFBVideoProvider_V4L_GetStreamDescription;
     thiz->PlayTo    = IDirectFBVideoProvider_V4L_PlayTo;
     thiz->Stop      = IDirectFBVideoProvider_V4L_Stop;
     thiz->GetStatus = IDirectFBVideoProvider_V4L_GetStatus;
     thiz->SeekTo    = IDirectFBVideoProvider_V4L_SeekTo;
     thiz->GetPos    = IDirectFBVideoProvider_V4L_GetPos;
     thiz->GetLength = IDirectFBVideoProvider_V4L_GetLength;
     thiz->GetColorAdjustment = IDirectFBVideoProvider_V4L_GetColorAdjustment;
     thiz->SetColorAdjustment = IDirectFBVideoProvider_V4L_SetColorAdjustment;
     thiz->SendEvent = IDirectFBVideoProvider_V4L_SendEvent;

     return DFB_OK;
}
