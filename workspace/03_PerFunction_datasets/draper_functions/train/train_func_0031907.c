ClassifySTTXTWord(WordList *keywordlists[], StyleContext &sc)
{
	char s[256] = { 0 };
	sc.GetCurrentLowered(s, sizeof(s));

 	if ((*keywordlists[0]).InList(s)) {
 		sc.ChangeState(SCE_STTXT_KEYWORD);
 	}

	else if ((*keywordlists[1]).InList(s)) {
		sc.ChangeState(SCE_STTXT_TYPE);
	}

	else if ((*keywordlists[2]).InList(s)) {
		sc.ChangeState(SCE_STTXT_FUNCTION);
	}

	else if ((*keywordlists[3]).InList(s)) {
		sc.ChangeState(SCE_STTXT_FB);
	}

	else if ((*keywordlists[4]).InList(s)) {
		sc.ChangeState(SCE_STTXT_VARS);
	}

	else if ((*keywordlists[5]).InList(s)) {
		sc.ChangeState(SCE_STTXT_PRAGMAS);
	}

	sc.SetState(SCE_STTXT_DEFAULT);
}
