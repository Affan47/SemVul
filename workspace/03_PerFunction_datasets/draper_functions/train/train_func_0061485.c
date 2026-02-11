merge_fileindex_audio(bgav_superindex_t * idx, bgav_stream_t * s)
  {
  int64_t pts;
  int i;

  for(i = s->first_index_position; i <= s->last_index_position; i++)
    {
    if(idx->entries[i].stream_id == s->stream_id)
      idx->entries[i].pts = BGAV_TIMESTAMP_UNDEFINED;
    }


  for(i = 0; i < s->file_index->num_entries; i++)
    {
    if(!i || (s->file_index->entries[i-1].position !=
              s->file_index->entries[i].position))
      {
      idx->entries[s->file_index->entries[i].position].pts =
        s->file_index->entries[i].pts;
      }
    }


  pts = s->duration;
  for(i = s->last_index_position; i >= s->first_index_position; i--)
    {
    if(idx->entries[i].stream_id != s->stream_id)
      continue;

    if(idx->entries[i].pts == BGAV_TIMESTAMP_UNDEFINED)
      idx->entries[i].pts = pts;
    else
      pts = idx->entries[i].pts;
    }


  idx->entries[0].duration = 0;
  bgav_superindex_set_durations(idx, s);


  }
