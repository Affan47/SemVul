GetClientRectangle() {
	PRectangle rc = wMain.GetClientPosition();
	if (verticalScrollBarVisible)
		rc.right -= scrollBarWidth;
	if (horizontalScrollBarVisible && (wrapState == eWrapNone))
		rc.bottom -= scrollBarHeight;

	rc.right -= rc.left;
	rc.bottom -= rc.top;
	rc.left = 0;
	rc.top = 0;
	return rc;
}
