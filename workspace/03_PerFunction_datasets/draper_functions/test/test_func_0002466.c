generateCPP()
{
	QProcess faustProcess;
	mItemBuildOptions = QFaustItem::mBuildOptions;
	faustProcess.start( mFaustPath + " -o " + cppFileQuoted() + " " + QFaustItem::mBuildOptions + " " + dspFileQuoted() );

	if (!faustProcess.waitForStarted())
	{
		mCppCode = "";
		return false;
	}

	if (!faustProcess.waitForFinished())
	{
		mCppCode = "";
		return false;
	}

	mCppCode = getFileContent( cppFile() );

	return true;
}
