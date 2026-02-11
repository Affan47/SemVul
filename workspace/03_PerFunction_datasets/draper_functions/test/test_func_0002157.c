HorizontalScrollTo(int xPos) {

	if (xPos < 0)
		xPos = 0;
	if ((wrapState == eWrapNone) && (xOffset != xPos)) {
		xOffset = xPos;
		SetHorizontalScrollPos();
		RedrawRect(GetClientRectangle());
	}
}
