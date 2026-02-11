draw( s32 index, const core::position2d<s32>& destPos,
		const core::rect<s32>* clip  )
{
	core::rect<s32> sourceRect;

	if( !Driver || index < 0 || index >= ImageCount )
	{
		return;
	}

	sourceRect.UpperLeftCorner.X = ( index % ImagesPerRow ) * ImageSize.Width;
	sourceRect.UpperLeftCorner.Y = ( index / ImagesPerRow ) * ImageSize.Height;
	sourceRect.LowerRightCorner.X = sourceRect.UpperLeftCorner.X + ImageSize.Width;
	sourceRect.LowerRightCorner.Y = sourceRect.UpperLeftCorner.Y + ImageSize.Height;

	Driver->draw2DImage( Texture, destPos, sourceRect, clip,
								video::SColor( 255, 255, 255, 255 ), UseAlphaChannel );
}
