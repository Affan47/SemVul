verify_read_command(cdrom_drive_t *d)
{
  int i;
  int16_t *buff=malloc(CDIO_CD_FRAMESIZE_RAW);
  int audioflag=0;
  int i_test_flags = d->i_test_flags;

  d->i_test_flags = 0;

  cdmessage(d,"Verifying drive can read CDDA...\n");

  d->enable_cdda(d,1);

  for(i=1;i<=d->tracks;i++){
    if(cdda_track_audiop(d,i)==1){
      long firstsector=cdda_track_firstsector(d,i);
      long lastsector=cdda_track_lastsector(d,i);
      long sector=(firstsector+lastsector)>>1;
      audioflag=1;

      if(d->read_audio(d,buff,sector,1)>0){
	cdmessage(d,"\tExpected command set reads OK.\n");
	d->enable_cdda(d,0);
	free(buff);
	d->i_test_flags = i_test_flags;
	return(0);
      }
    }
  }

  d->enable_cdda(d,0);

  if(!audioflag){
    cdmessage(d,"\tCould not find any audio tracks on this disk.\n");
    free(buff);
    return(-403);
  }

  cdmessage(d,"\n\tUnable to read any data; "
	    "drive probably not CDDA capable.\n");

  cderror(d,"006: Could not read any data from drive\n");

  free(buff);
  return(-6);
}
