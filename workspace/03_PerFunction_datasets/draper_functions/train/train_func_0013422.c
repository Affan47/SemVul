APanelChange(w, segments, nseg, curseg, cursorpos)
Widget w;
ICString *segments;
Cardinal nseg, curseg, cursorpos;
{
  AuxPanelWidget cpw = (AuxPanelWidget)w;
  Cardinal i;
  DisplaySegment *dseg;

  cpw->cpanel.numauxsegments = nseg;
  allocDisplaySegments(cpw, nseg);
  for (i = 0, dseg = cpw->cpanel.dispauxsegments ; i < nseg ; i++, dseg++) {


    copyString(segments +i, &dseg->seg);
    dseg->redrawpos = 0;
    dseg->width = 0;
  }
  Layout(cpw, False, False);
  if (XtIsRealized(w)) XClearWindow(XtDisplay(w), XtWindow(w));
  UpdateAuxDisplay(cpw);
  return;
}
