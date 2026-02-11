DrawWaveform(WaveTrack *track,
                               wxDC & dc,
                               const wxRect & r,
                               const ViewInfo *viewInfo,
                               bool drawEnvelope,
                               bool drawSamples,
                               bool drawSliders,
                               bool dB,
                               bool muted)
{
   DrawBackgroundWithSelection(&dc, r, track, blankSelectedBrush, blankBrush,
         viewInfo->sel0, viewInfo->sel1, viewInfo->h, viewInfo->zoom);

   for (WaveClipList::compatibility_iterator it = track->GetClipIterator(); it; it = it->GetNext())
      DrawClipWaveform(track, it->GetData(), dc, r, viewInfo,
                       drawEnvelope, drawSamples, drawSliders,
                       dB, muted);


   track->UpdateLocationsCache();

   for (int i = 0; i<track->GetNumCachedLocations(); i++) {
      WaveTrack::Location loc = track->GetCachedLocation(i);
      double x = (loc.pos - viewInfo->h) * viewInfo->zoom;
      if (x >= 0 && x < r.width) {
         dc.SetPen(*wxGREY_PEN);
         AColor::Line(dc, (int) (r.x + x - 1), r.y, (int) (r.x + x - 1), r.y + r.height);
         if (loc.typ == WaveTrack::locationCutLine) {
            dc.SetPen(*wxRED_PEN);
         }
         else {
            dc.SetPen(*wxBLACK_PEN);
         }
         AColor::Line(dc, (int) (r.x + x), r.y, (int) (r.x + x), r.y + r.height);
         dc.SetPen(*wxGREY_PEN);
         AColor::Line(dc, (int) (r.x + x + 1), r.y, (int) (r.x + x + 1), r.y + r.height);
      }
   }
}
