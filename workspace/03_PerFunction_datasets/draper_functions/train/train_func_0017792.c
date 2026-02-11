IDirectFBDataBuffer_Streamed_PeekData( IDirectFBDataBuffer *thiz,
                                       unsigned int         length,
                                       int                  offset,
                                       void                *data_buffer,
                                       unsigned int        *read_out )
{
     unsigned int len;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDataBuffer_Streamed)

     if (!data_buffer || !length || offset < 0)
          return DFB_INVARG;

     pthread_mutex_lock( &data->chunks_mutex );

     if (!data->chunks || (unsigned int) offset >= data->length) {
          pthread_mutex_unlock( &data->chunks_mutex );
          return data->finished ? DFB_EOF : DFB_BUFFEREMPTY;
     }


     len = MIN( length, data->length - offset );


     ReadChunkData( data, data_buffer, offset, len, false );


     if (read_out)
          *read_out = len;

     pthread_mutex_unlock( &data->chunks_mutex );

     return DFB_OK;
}
