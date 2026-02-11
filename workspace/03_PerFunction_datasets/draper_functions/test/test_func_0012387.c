addButton(const core::rect<s32>& rectangle, IGUIElement* parent, s32 id, const wchar_t* text, const wchar_t *tooltiptext)
{
	IGUIButton* button = new CGUIButton(this, parent ? parent : this, id, rectangle);
	if (text)
		button->setText(text);

	if ( tooltiptext )
		button->setToolTipText ( tooltiptext );

	button->drop();
	return button;
}
