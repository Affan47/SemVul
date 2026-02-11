undo_memory_add_blocks_from_stream (UNDO_MEMORY * memory,
				    UNDO_MEMORY_STREAM * stream)
{
  size_t pos, num_read;
  UNDO_MEMORY_STREAM_BLOCK_HEADER header;

  pos = 0;
  do
    {
      num_read = undo_memory_stream_read_header (stream, pos, &header);
      if (num_read != STREAM_SERIALIZED_BLOCK_HEADER_SIZE)
	{
	  UNDO_SUCCESS;
	}
      pos += num_read;

      if (MAP_NEW_ANON_AT (header.addr, header.size) != header.addr)
	{
	  UNDO_ERROR (UNDO_NOMEM);
	}
      undo_memory_block_header_record (memory, &header);

      num_read = stream->read (stream, pos, header.addr, header.size);
      pos += num_read;
    }
  while (1);
}
