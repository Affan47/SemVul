IDirectFBDataBuffer_File_SeekTo( IDirectFBDataBuffer *thiz,
                                 unsigned int         offset )
{
     DFBResult ret;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDataBuffer_File)

     if (!direct_stream_seekable( data->stream ))
          return DFB_UNSUPPORTED;

     pthread_mutex_lock( &data->mutex );
     ret = direct_stream_seek( data->stream, offset );
     pthread_mutex_unlock( &data->mutex );

     return ret;
}
