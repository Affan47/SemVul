update_source_track(mxf_file_t * f, mxf_klv_t * klv)
  {
  int i, j;
  mxf_track_t * t;
  mxf_package_t * p;
  mxf_preface_t * preface;
  mxf_content_storage_t * cs;

  int done = 0;

  preface = (mxf_preface_t*)f->header.preface;
  cs = (mxf_content_storage_t *)preface->content_storage;
  for(i = 0; i < cs->num_package_refs; i++)
    {
    if(cs->packages[i] &&
       cs->packages[i]->type == MXF_TYPE_SOURCE_PACKAGE)
      {
      p = (mxf_package_t*)(cs->packages[i]);
      for(j = 0; j < p->num_track_refs; j++)
        {
        t = (mxf_track_t*)(p->tracks[j]);
        if(!memcmp(t->track_number, &klv->key[12], 4))
          {
          done = 1;
          break;
          }
        }
      }
    if(done)
      break;
    }
  if(!done)
    return;
  t->num_packets++;
  if(klv->length > t->max_packet_size)
    t->max_packet_size = klv->length;
  }
