DropGraphics(bool freeObjects) {
	if (freeObjects) {
		delete pixmapLine;
		pixmapLine = 0;
		delete pixmapSelMargin;
		pixmapSelMargin = 0;
		delete pixmapSelPattern;
		pixmapSelPattern = 0;
		delete pixmapSelPatternOffset1;
		pixmapSelPatternOffset1 = 0;
		delete pixmapIndentGuide;
		pixmapIndentGuide = 0;
		delete pixmapIndentGuideHighlight;
		pixmapIndentGuideHighlight = 0;
	} else {
		if (pixmapLine)
			pixmapLine->Release();
		if (pixmapSelMargin)
			pixmapSelMargin->Release();
		if (pixmapSelPattern)
			pixmapSelPattern->Release();
		if (pixmapSelPatternOffset1)
			pixmapSelPatternOffset1->Release();
		if (pixmapIndentGuide)
			pixmapIndentGuide->Release();
		if (pixmapIndentGuideHighlight)
			pixmapIndentGuideHighlight->Release();
	}
}
