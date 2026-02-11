ftglue_stream_frame_exit( FT_Stream  stream )
{
  if ( stream->read )
  {
    FT_Memory  memory = stream->memory;

    FREE( stream->base );
  }
  stream->cursor = 0;
  stream->limit  = 0;

  LOG(( "ftglue:stream:frame_exit()\n" ));
}
