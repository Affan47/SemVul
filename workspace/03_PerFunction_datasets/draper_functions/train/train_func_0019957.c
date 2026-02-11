nsv_file_header_dump(nsv_file_header_t * h)
  {
  int i;
  bgav_dprintf( "file_header\n");

  bgav_dprintf( "  header_size:  %d\n", h->header_size);
  bgav_dprintf( "  file_size:    %d\n", h->file_size);
  bgav_dprintf( "  file_len:     %d\n", h->file_len);
  bgav_dprintf( "  metadata_len: %d\n", h->metadata_len);
  bgav_dprintf( "  toc_alloc:    %d\n", h->toc_alloc);
  bgav_dprintf( "  toc_size:     %d\n", h->toc_size);
  bgav_dprintf( "  title:        %s\n",
          (h->metadata.title ? h->metadata.title : "[not set]"));
  bgav_dprintf( "  url:          %s\n",
          (h->metadata.url ? h->metadata.url : "[not set]"));
  bgav_dprintf( "  creator:      %s\n",
          (h->metadata.creator ? h->metadata.creator : "[not set]"));
  bgav_dprintf( "  aspect:       %s\n",
          (h->metadata.aspect ? h->metadata.aspect : "[not set]"));
  bgav_dprintf( "  framerate:    %s\n",
          (h->metadata.framerate ? h->metadata.framerate : "[not set]"));

  if(h->toc_size)
    {
    if(h->toc.frames)
      {
      bgav_dprintf( "  TOC version 2 (%d entries)\n", h->toc_size);
      for(i = 0; i < h->toc_size; i++)
        bgav_dprintf( "    frame: %d, offset: %d\n",
                h->toc.frames[i], h->toc.offsets[i]);
      }
    else
      {
      bgav_dprintf( "  TOC version 1 (%d entries)\n", h->toc_size);
      for(i = 0; i < h->toc_size; i++)
        bgav_dprintf( "    offset: %d\n", h->toc.offsets[i]);
      }
    }
  else
    bgav_dprintf( "  No TOC\n");
  }
