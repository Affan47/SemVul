Draw( GRA_wxWidgets *graphicsOutput, wxDC &dc )
{
  int xmin, ymin, xmax, ymax;
  graphicsOutput->GetLimits( xmin, ymin, xmax, ymax );
  for( int x=0; x<width_; ++x )
  {
    for( int y=0; y<height_; ++y )
    {
      wxPen wxpen( dc.GetPen() );
      wxpen.SetColour( ExGlobals::GetwxColor(bitmap_[x+y*width_]) );
      dc.SetPen( wxpen );
      dc.DrawPoint( x+ixLo_, ymax-(y+iyLo_) );
    }
  }
}
