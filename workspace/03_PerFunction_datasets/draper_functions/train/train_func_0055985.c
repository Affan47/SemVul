getThresholdBasedOnTPR( InputData* pData, vector<AlphaReal>& posteriors, const AlphaReal expectedTPR, AlphaReal& TPR, AlphaReal& FPR )
	{
		const int numOfExamples = pData->getNumExamples();
		vector<int> numPerClasses(2);
		int TP=0,FP=0;
		FeatureReal threshold=numeric_limits<FeatureReal>::max();

		vector<pair<AlphaReal,int> > sortedPosteriors(posteriors.size());

		for(int i=0; i<numOfExamples; ++i )
		{

			sortedPosteriors[i].first = posteriors[i];

			vector<Label>& labels = pData->getLabels(i);

			if (labels[_positiveLabelIndex].y>0)

			{
				sortedPosteriors[i].second=1;
			} else {
				sortedPosteriors[i].second=0;
			}
		}

		sort( sortedPosteriors.begin(), sortedPosteriors.end(),
			 nor_utils::comparePair< 1, AlphaReal, int, greater<AlphaReal> >() );


		fill(numPerClasses.begin(),numPerClasses.end(), 0 );
		for (int i = 0; i < numOfExamples; ++i)
		{
			vector<Label>& labels = pData->getLabels(i);
			vector<Label>::iterator lIt;

			for ( lIt = labels.begin(); lIt != labels.end(); ++lIt )
			{
				if ( lIt->y > 0 )
					numPerClasses[lIt->idx]++;
			}

		}


		FP=TP=0;
		threshold=static_cast<FeatureReal>(sortedPosteriors[0].first)+numeric_limits<FeatureReal>::min();

		for(int i=0; i<numOfExamples; ++i )
		{

			if (sortedPosteriors[i].second) TP++;
			else FP++;


			AlphaReal currentTPR = TP / static_cast<AlphaReal>(numPerClasses[_positiveLabelIndex]);


			if ((i>0)&&(sortedPosteriors[i-1].first!=sortedPosteriors[i].first))
			{
				threshold=(sortedPosteriors[i-1].first+sortedPosteriors[i].first)/2;
				if ( currentTPR > expectedTPR ) {
					break;
				}
			}

		}

		TPR = TP/static_cast<AlphaReal>(numPerClasses[_positiveLabelIndex]);
		FPR = FP/static_cast<AlphaReal>(numPerClasses[1-_positiveLabelIndex]);

		return threshold;
	}
