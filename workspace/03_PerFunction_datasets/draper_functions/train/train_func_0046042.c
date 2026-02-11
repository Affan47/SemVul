draw3DButtonPaneStandard(IGUIElement* element,
					const core::rect<s32>& r,
					const core::rect<s32>* clip)
{
	if (!Driver)
		return;

	core::rect<s32> rect = r;

	if ( Type == EGST_BURNING_SKIN )
	{
		rect.UpperLeftCorner.X -= 1;
		rect.UpperLeftCorner.Y -= 1;
		rect.LowerRightCorner.X += 1;
		rect.LowerRightCorner.Y += 1;
		draw3DSunkenPane(element,
					getColor( EGDC_WINDOW ).getInterpolated( 0xFFFFFFFF, 0.9f )
					,false, true, rect, clip);
		return;
	}

	Driver->draw2DRectangle(getColor(EGDC_3D_DARK_SHADOW), rect, clip);

	rect.LowerRightCorner.X -= 1;
	rect.LowerRightCorner.Y -= 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_HIGH_LIGHT), rect, clip);

	rect.UpperLeftCorner.X += 1;
	rect.UpperLeftCorner.Y += 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_SHADOW), rect, clip);

	rect.LowerRightCorner.X -= 1;
	rect.LowerRightCorner.Y -= 1;

	if (!UseGradient)
	{
		Driver->draw2DRectangle(getColor(EGDC_3D_FACE), rect, clip);
	}
	else
	{
		const video::SColor c1 = getColor(EGDC_3D_FACE);
		const video::SColor c2 = c1.getInterpolated(getColor(EGDC_3D_DARK_SHADOW), 0.4f);
		Driver->draw2DRectangle(rect, c1, c1, c2, c2, clip);
	}
}
