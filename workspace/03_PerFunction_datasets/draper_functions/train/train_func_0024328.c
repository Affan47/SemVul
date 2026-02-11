CallTipStart(int pos, Point pt, int textHeight, const char *defn,
                                 const char *faceName, int size,
                                 int codePage_, int characterSet,
								 int technology, Window &wParent) {
	clickPlace = 0;
	delete []val;
	val = 0;
	val = new char[strlen(defn) + 1];
	strcpy(val, defn);
	codePage = codePage_;
	Surface *surfaceMeasure = Surface::Allocate(technology);
	if (!surfaceMeasure)
		return PRectangle();
	surfaceMeasure->Init(wParent.GetID());
	surfaceMeasure->SetUnicodeMode(SC_CP_UTF8 == codePage);
	surfaceMeasure->SetDBCSMode(codePage);
	startHighlight = 0;
	endHighlight = 0;
	inCallTipMode = true;
	posStartCallTip = pos;
	int deviceHeight = surfaceMeasure->DeviceHeightFont(size);
	FontParameters fp(faceName, deviceHeight / SC_FONT_SIZE_MULTIPLIER, SC_WEIGHT_NORMAL, false, 0, technology, characterSet);
	font.Create(fp);


	int numLines = 1;
	const char *newline;
	const char *look = val;
	rectUp = PRectangle(0,0,0,0);
	rectDown = PRectangle(0,0,0,0);
	offsetMain = insetX;
	int width = PaintContents(surfaceMeasure, false) + insetX;
	while ((newline = strchr(look, '\n')) != NULL) {
		look = newline + 1;
		numLines++;
	}
	lineHeight = surfaceMeasure->Height(font);


	int height = lineHeight * numLines - surfaceMeasure->InternalLeading(font) + borderHeight * 2;
	delete surfaceMeasure;
	if (above) {
		return PRectangle(pt.x - offsetMain, pt.y - verticalOffset - height, pt.x + width - offsetMain, pt.y - verticalOffset);
	} else {
		return PRectangle(pt.x - offsetMain, pt.y + verticalOffset + textHeight, pt.x + width - offsetMain, pt.y + verticalOffset + textHeight + height);
	}
}
