CGUIComboBox(IGUIEnvironment* environment, IGUIElement* parent,
	s32 id, core::rect<s32> rectangle)
	: IGUIComboBox(environment, parent, id, rectangle),
	ListButton(0), SelectedText(0), ListBox(0), LastFocus(0),
	Selected(-1), HAlign(EGUIA_UPPERLEFT), VAlign(EGUIA_CENTER), HasFocus(false)
{
	#ifdef _DEBUG
	setDebugName("CGUIComboBox");
	#endif

	IGUISkin* skin = Environment->getSkin();

	s32 width = 15;
	if (skin)
		width = skin->getSize(EGDS_WINDOW_BUTTON_WIDTH);

	core::rect<s32> r;
	r.UpperLeftCorner.X = rectangle.getWidth() - width - 2;
	r.LowerRightCorner.X = rectangle.getWidth() - 2;

	r.UpperLeftCorner.Y = 2;
	r.LowerRightCorner.Y = rectangle.getHeight() - 2;

	ListButton = Environment->addButton(r, this, -1, L"");
	if (skin && skin->getSpriteBank())
	{
		ListButton->setSpriteBank(skin->getSpriteBank());
		ListButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_CURSOR_DOWN), skin->getColor(EGDC_WINDOW_SYMBOL));
		ListButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_CURSOR_DOWN), skin->getColor(EGDC_WINDOW_SYMBOL));
	}
	ListButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	ListButton->setSubElement(true);
	ListButton->setTabStop(false);

	r.UpperLeftCorner.X = 2;
	r.UpperLeftCorner.Y = 2;
	r.LowerRightCorner.X = RelativeRect.getWidth() - (ListButton->getAbsolutePosition().getWidth() + 2);
	r.LowerRightCorner.Y = RelativeRect.getHeight() - 2;

	SelectedText = Environment->addStaticText(L"", r, false, false, this, -1, false);
	SelectedText->setSubElement(true);
	SelectedText->setAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	SelectedText->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_CENTER);
	if (skin)
		SelectedText->setOverrideColor(skin->getColor(EGDC_BUTTON_TEXT));
	SelectedText->enableOverrideColor(true);


	setTabStop(true);
	setTabOrder(-1);
}
