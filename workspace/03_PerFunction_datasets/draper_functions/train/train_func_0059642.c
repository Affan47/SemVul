findOverlayGroup(Uint16 currentGroup)
{
  int allocated[16];
  size_t i, max;
  Uint16 group = 0;

  for (i=0; i<16; i++) allocated[i]=0;
  max = overlayList.size();
  for (i=0; i<max; i++)
  {
    group = getOverlayInPresentationStateGroup(i);
    if ((group >= 0x6000)&&(group <= 0x601F)) allocated[(Uint16)(group - 0x6000) >> 1] = 2;
  }
  max = getNumberOfOverlaysInImage();
  for (i=0; i<max; i++)
  {
    group = getOverlayInImageGroup(i);
    if ((group >= 0x6000)&&(group <= 0x601F)) allocated[(Uint16)(group - 0x6000) >> 1] += 1;
  }


  if ((currentGroup >= 0x6000)&&(currentGroup <= 0x601F))
  {
    if (allocated[(Uint16)(group - 0x6000) >> 1] == 2) return currentGroup;
  }

  for (i=0; i<16; i++) if (allocated[i]==0) return 0x6000+(i<<1);

  for (i=0; i<16; i++) if (allocated[i]<2) return 0x6000+(i<<1);

  return 0;
}
