floodFillColor( const Geometry &point_,
				    const Magick::Color &fillColor_ )
{
  floodFillTexture( point_, Image( Geometry( 1, 1), fillColor_) );
}
