direct_stream_remote( DirectStream *stream )
{
     D_ASSERT( stream != NULL );

     D_MAGIC_ASSERT( stream, DirectStream );

#if DIRECT_BUILD_NETWORK
     if (stream->remote.host)
          return true;
#endif
     return false;
}
