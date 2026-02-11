WordListSet(int n, const char *wl) {
	WordList *wordListN = 0;
	switch (n) {
	case 0:
		wordListN = &keywords;
		break;
	case 1:
		wordListN = &keywords2;
		break;
	case 2:
		wordListN = &keywords3;
		break;
	case 3:
		wordListN = &keywords4;
		break;
	case 4:
		wordListN = &keywords5;
		break;
	case 5:
		wordListN = &keywords6;
		break;
	case 6:
		wordListN = &keywords7;
		break;
	}
	int firstModification = -1;
	if (wordListN) {
		WordList wlNew;
		wlNew.Set(wl);
		if (*wordListN != wlNew) {
			wordListN->Set(wl);
			firstModification = 0;
		}
	}
	return firstModification;
}
