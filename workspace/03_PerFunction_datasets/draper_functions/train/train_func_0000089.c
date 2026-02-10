classifyFoldPointMetapost(const char* s,WordList *keywordlists[]) {
	WordList& keywordsStart=*keywordlists[3];
	WordList& keywordsStop1=*keywordlists[4];

	if (keywordsStart.InList(s)) {return 1;}
	else if (keywordsStop1.InList(s)) {return -1;}
	return 0;

}
