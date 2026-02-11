freeDisplaySegments(cpw)
AuxPanelWidget cpw;
{
  Cardinal i;
  DisplaySegment *dseg = cpw->cpanel.dispauxsegments;

  for (i = 0 ; i < cpw->cpanel.dispauxsegmentsize ; i++, dseg++) {
    if (dseg->seg.data != NULL) XtFree(dseg->seg.data);
  }
  XtFree((char *)cpw->cpanel.dispauxsegments);
  cpw->cpanel.dispauxsegments = (DisplaySegment *)0;
  cpw->cpanel.dispauxsegmentsize = 0;
}
