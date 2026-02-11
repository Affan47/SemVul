updateAbsolutePosition()
{
	if (Parent)
		DesiredRect.LowerRightCorner.X = Parent->getAbsolutePosition().getWidth();

	IGUIElement::updateAbsolutePosition();
}
