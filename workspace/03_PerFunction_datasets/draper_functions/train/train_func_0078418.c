Rd_read_block( struct Range_decoder * const rdec )
  {
  if( !rdec->at_stream_end )
    {
    rdec->stream_pos = readblock( rdec->infd, rdec->buffer, rd_buffer_size );
    if( rdec->stream_pos != rd_buffer_size && errno )
      { show_error( "Read error", errno, false ); cleanup_and_fail( 1 ); }
    rdec->at_stream_end = ( rdec->stream_pos < rd_buffer_size );
    rdec->partial_member_pos += rdec->pos;
    rdec->pos = 0;
    }
  return rdec->pos < rdec->stream_pos;
  }
