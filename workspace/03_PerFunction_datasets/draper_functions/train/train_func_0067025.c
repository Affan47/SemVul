direct_stream_seekable( DirectStream *stream )
{
     D_ASSERT( stream != NULL );

     D_MAGIC_ASSERT( stream, DirectStream );

     return stream->seek ? true : false;
}
