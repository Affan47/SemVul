floodFillColor( const Geometry &point_,
				    const Magick::Color &fillColor_,
				    const Magick::Color &borderColor_ )
{
  floodFillTexture( point_, Image( Geometry( 1, 1), fillColor_),
                    borderColor_ );
}
