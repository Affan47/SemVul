direct_stream_read( DirectStream *stream,
                    unsigned int  length,
                    void         *buf,
                    unsigned int *read_out )
{
     D_ASSERT( stream != NULL );
     D_ASSERT( length != 0 );
     D_ASSERT( buf != NULL );

     D_MAGIC_ASSERT( stream, DirectStream );

     if (stream->length >= 0 && stream->offset >= stream->length)
          return DR_EOF;

     if (stream->read)
          return stream->read( stream, length, buf, read_out );

     return DR_UNSUPPORTED;
}
