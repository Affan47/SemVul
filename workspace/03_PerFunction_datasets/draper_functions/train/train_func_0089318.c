direct_stream_peek( DirectStream *stream,
                    unsigned int  length,
                    int           offset,
                    void         *buf,
                    unsigned int *read_out )
{
     D_ASSERT( stream != NULL );
     D_ASSERT( length != 0 );
     D_ASSERT( buf != NULL );

     D_MAGIC_ASSERT( stream, DirectStream );

     if (stream->length >= 0 && (stream->offset + offset) >= stream->length)
          return DR_EOF;

     if (stream->peek)
          return stream->peek( stream, length, offset, buf, read_out );

     return DR_UNSUPPORTED;
}
