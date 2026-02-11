updateAbsolutePosition()
{
	core::rect<s32> parentRect(0,0,0,0);

	if (Parent)
	{
		parentRect = Parent->getAbsolutePosition();
		RelativeRect.UpperLeftCorner.X = 0;
		RelativeRect.UpperLeftCorner.Y = 0;
		RelativeRect.LowerRightCorner.X = parentRect.getWidth();
		RelativeRect.LowerRightCorner.Y = parentRect.getHeight();
	}

	IGUIElement::updateAbsolutePosition();
}
