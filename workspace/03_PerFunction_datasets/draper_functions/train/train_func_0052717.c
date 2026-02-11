resettitle()
{
#ifdef KANJI
	char_u	*	t = NULL;
	char_u	*	i = NULL;

	if (lasttitle != NULL)
		t = kanjiconvsto(lasttitle, toupper(JP_DISP), TRUE);
	if (lasticon != NULL)
		i = kanjiconvsto(lasticon, toupper(JP_DISP), TRUE);
	mch_settitle(t, i);
	if (t != NULL)
		free(t);
	if (i != NULL)
		free(i);
#else
	mch_settitle(lasttitle, lasticon);
#endif
}
