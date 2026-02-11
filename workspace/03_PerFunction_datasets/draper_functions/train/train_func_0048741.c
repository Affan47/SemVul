AbandonPaint() {
	if ((paintState == painting) && !paintingAllText) {
		paintState = paintAbandoned;
	}
	return paintState == paintAbandoned;
}
