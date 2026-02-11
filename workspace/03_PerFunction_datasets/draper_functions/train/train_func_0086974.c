subCopyState(BaseLearner *pBaseLearner)
	{
		SingleStumpLearner::subCopyState(pBaseLearner);
		HaarLearner::subCopyState(dynamic_cast<HaarLearner*>(pBaseLearner));
	}
