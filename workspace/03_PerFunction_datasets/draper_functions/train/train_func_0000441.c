trainpolicy( InputData* pTrainingData, const string baseLearnerName, const int numIterations, const int arrayInd )
	{
		AdaBoostMHLearner* sHypothesis = new AdaBoostMHLearner();
		sHypothesis->run(_args, pTrainingData, baseLearnerName, numIterations, _weakhyp );
		delete sHypothesis;

		_baseLearnerName = baseLearnerName;

		const int numExamples = pTrainingData->getNumExamples();

		vector<AlphaReal> results(_actionNum);
		int numErrors = 0;
		for(int i=0; i<numExamples; ++i )
		{
			fill(results.begin(),results.end(),0.0);
			for(int t=0; t<_weakhyp.size(); ++t)
			{
				for( int l=0; l<_actionNum; ++l )
				{
					results[l] += _weakhyp[t]->getAlpha() * _weakhyp[t]->classify(pTrainingData,i,l);
				}
			}
			AlphaReal maxMargin = -numeric_limits<AlphaReal>::max();
			int forecastlabel = -1;

			for(int l=0; l<_actionNum; ++l )
			{
				if (results[l]>maxMargin)
				{
					maxMargin=results[l];
					forecastlabel=l;
				}
			}

			vector<Label> labels = pTrainingData->getLabels(i);

			if (pTrainingData->hasLabel(i,forecastlabel) )
			{
				if(labels[forecastlabel].y<0) numErrors++;
			} else numErrors++;
		}

		AlphaReal error = (AlphaReal)numErrors/(AlphaReal) numExamples;
		return error;
	}
