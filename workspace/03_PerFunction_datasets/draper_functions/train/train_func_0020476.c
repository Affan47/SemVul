ogg_sync_reset(ogg_sync_state *oy){
  if(ogg_sync_check(oy))return -1;

  oy->fill=0;
  oy->returned=0;
  oy->unsynced=0;
  oy->headerbytes=0;
  oy->bodybytes=0;
  return(0);
}
