ftglue_stream_seek( FT_Stream   stream,
                    FT_Long     pos )
{
  FT_Error  error = 0;

  if ( stream->read )
  {
    if ( stream->read( stream, pos, 0, 0 ) )
      error = FT_Err_Invalid_Stream_Operation;
  }
  else if ( pos < 0 || (FT_ULong) pos > stream->size )
    error = FT_Err_Invalid_Stream_Operation;

  if ( !error )
    stream->pos = pos;
  LOG(( "ftglue:stream:seek(%ld) -> %d\n", pos, error ));
  return error;
}
