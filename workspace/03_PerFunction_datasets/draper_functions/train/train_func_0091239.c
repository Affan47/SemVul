egFixup(void)
#else
egFixup()
#endif
{
  int               i;
  ExceptionGroup    *nextEG;
  ExceptionGroup    *innerEG;

  for (i=1; i<=highWater ; i++) {
    for (innerEG=egArray[i]; innerEG != NULL ; innerEG=nextEG) {
      nextEG=innerEG->pendingLink;
      innerEG->pendingLink=NULL;
    };
    egArray[i]=NULL;
  };
  lastEG=NULL;
  lastBlkLevel=0;
}
