display_toc(cdrom_drive *d){
  long audiolen=0;
  int i;
  report("\nTable of contents (audio tracks only):\n"
	 "track        length               begin        copy pre ch\n"
	 "===========================================================");

  for(i=1;i<=d->tracks;i++)
    if(cdda_track_audiop(d,i)>0){

      long sec=cdda_track_firstsector(d,i);
      long off=cdda_track_lastsector(d,i)-sec+1;

      report("%3d.  %7ld [%02d:%02d.%02d]  %7ld [%02d:%02d.%02d]  %s %s %s",
	     i,
	     off,(int)(off/(60*75)),(int)((off/75)%60),(int)(off%75),
	     sec,(int)(sec/(60*75)),(int)((sec/75)%60),(int)(sec%75),
	     cdda_track_copyp(d,i)?"  OK":"  no",
	     cdda_track_preemp(d,i)?" yes":"  no",
	     cdda_track_channels(d,i)==2?" 2":" 4");
      audiolen+=off;
    }
  report("TOTAL %7ld [%02d:%02d.%02d]    (audio only)",
	 audiolen,(int)(audiolen/(60*75)),(int)((audiolen/75)%60),
	 (int)(audiolen%75));
  report(" ");
}
