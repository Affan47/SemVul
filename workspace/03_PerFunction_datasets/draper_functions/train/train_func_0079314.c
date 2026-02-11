draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	video::IVideoDriver* driver = Environment->getVideoDriver();


	const core::position2di spritePos = AbsoluteRect.getCenter();

	if (!Pressed)
	{
		if (DrawBorder)
			skin->draw3DButtonPaneStandard(this, AbsoluteRect, &AbsoluteClippingRect);

		if (Image)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= ImageRect.getWidth() / 2;
			pos.Y -= ImageRect.getHeight() / 2;

			driver->draw2DImage(Image,
					ScaleImage? AbsoluteRect :
						core::recti(pos, ImageRect.getSize()),
					ImageRect, &AbsoluteClippingRect,
					0, UseAlphaChannel);
		}
		if (SpriteBank && ButtonSprites[EGBS_BUTTON_UP].Index != -1)
		{

			SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_UP].Index, spritePos,
				&AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_UP].Color, ClickTime, os::Timer::getTime(),
				ButtonSprites[EGBS_BUTTON_UP].Loop, true);
		}
	}
	else
	{
		if (DrawBorder)
			skin->draw3DButtonPanePressed(this, AbsoluteRect, &AbsoluteClippingRect);

		if (PressedImage)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= PressedImageRect.getWidth() / 2;
			pos.Y -= PressedImageRect.getHeight() / 2;

			if (Image == PressedImage && PressedImageRect == ImageRect)
			{
				pos.X += 1;
				pos.Y += 1;
			}
			driver->draw2DImage(PressedImage,
					ScaleImage? AbsoluteRect :
						core::recti(pos, PressedImageRect.getSize()),
					PressedImageRect, &AbsoluteClippingRect,
					0, UseAlphaChannel);
		}

		if (SpriteBank && ButtonSprites[EGBS_BUTTON_DOWN].Index != -1)
		{

			SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_DOWN].Index, spritePos,
				&AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_DOWN].Color, ClickTime, os::Timer::getTime(),
				ButtonSprites[EGBS_BUTTON_DOWN].Loop, true);
		}
	}

	if (Text.size())
	{
		IGUIFont* font = OverrideFont;
		if (!OverrideFont)
			font = skin->getFont(EGDF_BUTTON);

		core::rect<s32> rect = AbsoluteRect;
		if (Pressed)
			rect.UpperLeftCorner.Y += 2;

		if (font)
			font->draw(Text.c_str(), rect,
				skin->getColor(IsEnabled ? EGDC_BUTTON_TEXT : EGDC_GRAY_TEXT),
				true, true, &AbsoluteClippingRect);
	}

	IGUIElement::draw();
}
