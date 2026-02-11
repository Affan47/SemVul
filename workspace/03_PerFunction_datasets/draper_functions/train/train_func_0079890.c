IDirectFBDataBuffer_File_WaitForData( IDirectFBDataBuffer *thiz,
                                      unsigned int         length )
{
     DFBResult ret;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDataBuffer_File)

     pthread_mutex_lock( &data->mutex );
     ret = direct_stream_wait( data->stream, length, NULL );
     pthread_mutex_unlock( &data->mutex );

     return ret;
}
