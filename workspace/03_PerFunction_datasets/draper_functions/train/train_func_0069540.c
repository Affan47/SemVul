PlayRegionColor(wxDC * dc, bool locked)
{
   if (!inited)
      Init();
   dc->SetPen(playRegionPen[(int)locked]);
   dc->SetBrush(playRegionBrush[(int)locked]);
}
