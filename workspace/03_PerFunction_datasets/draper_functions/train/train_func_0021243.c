get_feeder_type_LS30 (Coolscan_t * s)
{
  int size;
  unsigned char *ptr;
  int ima;


  size=get_inquiery_part_LS30(s, (unsigned char) 1);
  if(strncmp((char *)s->buffer+5,"Strip",5)==0)
  { s->feeder=STRIP_FEEDER;
    s->autofeeder = 1;
  }
  if(strncmp((char *)s->buffer+5,"Mount",5)==0)
  { s->feeder=MOUNT_FEEDER;
  }

  if(s->feeder==STRIP_FEEDER)
  { size=coolscan_read_var_data_block (s,(int)0x88);
    if(size>=4)
    { s->numima=s->buffer[3];
      if(s->numima>6) s->numima=6;
      if(s->numima>(size-4)/16) s->numima=(size-4)/16;
      ptr=s->buffer+4;
      for(ima=0;ima<s->numima;ima++)
      {  s->ipos[ima].start=getnbyte(ptr,4);
         s->ipos[ima].offset=getnbyte(ptr+4,4);
         s->ipos[ima].end=getnbyte(ptr+8,4);
         s->ipos[ima].height=getnbyte(ptr+12,4);
	 ptr+=16;
      }
    }
    s->posima=0;
  }
  return 1;
}
