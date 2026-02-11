ChangeSize() {
	DropGraphics(false);
	SetScrollBars();
	if (Wrapping()) {
		PRectangle rcTextArea = GetClientRectangle();
		rcTextArea.left = vs.textStart;
		rcTextArea.right -= vs.rightMarginWidth;
		if (wrapWidth != rcTextArea.Width()) {
			NeedWrapping();
			Redraw();
		}
	}
}
