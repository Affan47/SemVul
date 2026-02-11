switchVc(bool enter)
{
	mOffsetCur = 0;
	setupOffset();

	setupPalette(!enter);
	if (enter && mPalette) eraseMargin(true, mRows);
}
