_hb_stream_frame_enter( HB_Stream stream,
			HB_UInt count )
{
  HB_Error  error = HB_Err_Ok;


  if (HB_UNLIKELY (stream->pos + count > stream->size ||
		   stream->pos + count < stream->pos))
  {
    error = ERR(HB_Err_Read_Error);
    goto Exit;
  }


  stream->cursor = stream->base + stream->pos;
  stream->pos   += count;

Exit:
  LOG(( "_hb_stream_frame_enter(%ld) -> 0x%04X\n", count, error ));
  return error;
}
