addButton(s32 id, const wchar_t* text,const wchar_t* tooltiptext,
	video::ITexture* img, video::ITexture* pressed, bool isPushButton,
	bool useAlphaChannel)
{
	ButtonX += 3;

	core::rect<s32> rectangle(ButtonX,2,ButtonX+1,3);
	if ( img )
	{
		const core::dimension2du &size = img->getOriginalSize();
		rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + size.Width + 8;
		rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + size.Height + 6;
	}

	if ( text )
	{
		IGUISkin* skin = Environment->getSkin();
		IGUIFont * font = skin->getFont(EGDF_BUTTON);
		if ( font )
		{
			core::dimension2d<u32> dim = font->getDimension(text);
			if ( (s32)dim.Width > rectangle.getWidth() )
				rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + dim.Width + 8;
			if ( (s32)dim.Height > rectangle.getHeight() )
				rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + dim.Height + 6;
		}
	}

	ButtonX += rectangle.getWidth();

	IGUIButton* button = new CGUIButton(Environment, this, id, rectangle);
	button->drop();

	if (text)
		button->setText(text);

	if (tooltiptext)
		button->setToolTipText(tooltiptext);

	if (img)
		button->setImage(img);

	if (pressed)
		button->setPressedImage(pressed);

	if (isPushButton)
		button->setIsPushButton(isPushButton);

	if (useAlphaChannel)
		button->setUseAlphaChannel(useAlphaChannel);

	return button;
}
