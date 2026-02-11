getNextAction( InputData* state, const int arrayInd )
	{
		vector<AlphaReal> forecast(_actionNum);


		getExplorationDistribution(state, forecast);

		AlphaReal maxMargin = -numeric_limits<AlphaReal>::max();
		int forecastlabel = -1;
		AlphaReal tmpVal = forecast[0];
		int allEqual = 1;

		for(int l=0; l<_actionNum; ++l )
		{
			if (forecast[l]>maxMargin)
			{
				maxMargin=forecast[l];
				forecastlabel=l;
			}

			if ( ! nor_utils::is_zero(forecast[l]-tmpVal) )
			{
				allEqual=0;
			}
		}


		if (allEqual)
		{
			forecastlabel=rand() % _actionNum;
		} else {

		}


		return forecastlabel;
	}
