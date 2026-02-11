doAddDevice(bool keep)
{
	outDebug(5, std::cout << "Update Line " << std::endl);

	std::stringstream newLine;
	newLine << ConfigurationEditor::normalizeNum(mCandidateLine->getToken(0),4,16);
	newLine <<  " " << mCandidateLine->getMultiToken(1,0) << "\n";
	mCandidateLine->replaceLine(newLine.str());

	if (mCandidateLine != NULL)
	{
		if (keep && mCandidateLine->isNew())
			mConfigFile->addDev(mCandidateLine);
		mCandidateLine = NULL;
	}
	initialize();
}
