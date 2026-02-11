init(float radius)
{
	setRadius( radius );
	mHighlightedInteractionIndex = -1;
	mOriginAngle = 0;
	mIsPaletteEnabled = true;
	mPositioningPolicy = CENTER_POLICY;
	setVisible(false);

	mHighlightPen = PALETTE_HIGHLIGHT_PEN;
	mHighlightBrush = PALETTE_HIGHLIGHT_BRUSH;


	QPaletteManager::instance()->registerPalette( this );
}
