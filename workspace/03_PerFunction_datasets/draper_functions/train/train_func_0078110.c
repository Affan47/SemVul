updateFont(Font oldfid_)
{
  Font fid=MSWidget::font();
  if (fid!=oldfid_)
   {
     if (oldfid_==subtitleFont()) _subtitleFont=fid;
     if (oldfid_==mintitleFont()) _mintitleFont=fid;
     if (oldfid_==maxtitleFont()) _maxtitleFont=fid;
     if (oldfid_==labelFont()) _labelFont=fid;
     if (oldfid_==valueFont()) valueWin()->font(fid);
     computeSize();
     redraw();
   }
}
