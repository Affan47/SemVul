bgav_sdp_get_attr_int(bgav_sdp_attr_t * attrs, int num_attrs,
                          const char * name, int* ret)
  {
  int i;
  for(i = 0; i < num_attrs; i++)
    {
    if(!strcmp(attrs[i].name, name))
      {
      if(attrs[i].type != BGAV_SDP_TYPE_INT)
        return 0;
      *ret = attrs[i].val.i;
      return 1;
      }
    }
  return 0;
  }
