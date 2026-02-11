fix_b_pyramid(bgav_superindex_t * idx,
                          bgav_stream_t * s, int num_entries)
  {
  int i, index, min_index;
  int next_ip_frame;
  fix_b_entries * entries;
  int64_t pts;


  entries = malloc(num_entries * sizeof(*entries));
  index = 0;
  for(i = 0; i  < idx->num_entries; i++)
    {
    if(idx->entries[i].stream_id == s->stream_id)
      {
      entries[index].index = i;
      entries[index].pts = idx->entries[i].pts;
      entries[index].duration = idx->entries[i].duration;
      entries[index].type = idx->entries[i].flags & 0xff;
      entries[index].done = 0;
      index++;
      }
    }


  pts = entries[0].pts;
  pts += entries[0].duration;
  entries[0].done = 1;

  index = 1;

  while(1)
    {
    next_ip_frame = index+1;

    while((next_ip_frame < num_entries) &&
          (entries[next_ip_frame].type == BGAV_CODING_TYPE_B))
      {
      next_ip_frame++;
      }


    if(next_ip_frame == index + 1)
      {
      entries[index].pts = pts;
      pts += entries[index].duration;
      }
    else
      {
      for(i = index; i < next_ip_frame; i++)
        {
        min_index = find_min(entries, index, next_ip_frame);
        if(min_index < 0)
          break;
        entries[min_index].pts = pts;
        entries[min_index].done = 1;
        pts += entries[min_index].duration;
        }
      }

    if(next_ip_frame >= num_entries)
      break;
    index = next_ip_frame;
    }


  for(i = 0; i < num_entries; i++)
    idx->entries[entries[i].index].pts = entries[i].pts;

  free(entries);
  }
