Draw( GRA_wxWidgets *graphicsOutput, wxDC &dc )
{
  std::vector<GRA_polyline*>::const_iterator pEnd = polylines_.end();
  for( std::vector<GRA_polyline*>::const_iterator i=polylines_.begin(); i!=pEnd; ++i )
    (*i)->Draw( graphicsOutput, dc );
  std::vector<GRA_drawableText*>::const_iterator tEnd = textVec_.end();
  maxWidth_ = 0.0;
  for( std::vector<GRA_drawableText*>::const_iterator i=textVec_.begin(); i!=tEnd; ++i )
  {
    (*i)->Draw( graphicsOutput, dc );
    double width = (*i)->GetWidth();
    if( maxWidth_ < width )maxWidth_ = width;
  }
}
