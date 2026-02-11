findBreakBackwards(int& breakPos, QString text, QFontMetrics* fm, int maxWidth)
{
	int usedWidth;


	breakPos = 0;
	usedWidth = fm->width(text);
	if (usedWidth < maxWidth)
		return usedWidth;


	int topPos = text.length();
	while(1) {
		int halfPos = (breakPos + topPos)/2;
		int halfWidth = fm->width(text.mid(halfPos));
		if (halfWidth > maxWidth) {
		    topPos = halfPos-1;
		    continue;
		}
		breakPos = halfPos;
		usedWidth = halfWidth;
		if (topPos - breakPos <3) break;
	}


	QChar::Category lastCat, cat;
	int pos = breakPos;
	lastCat = text[pos].category();

	while (pos < text.length()-2) {
		pos++;
		cat = text[pos].category();
		if (cat == lastCat) continue;


		if ((lastCat == QChar::Letter_Uppercase) &&
				(cat == QChar::Letter_Lowercase)) {
			lastCat = cat;
			continue;
		}
		lastCat = cat;

		breakPos = pos;
		usedWidth = fm->width(text.mid(breakPos));
		if (usedWidth < maxWidth) break;
	}
	return usedWidth;
}
