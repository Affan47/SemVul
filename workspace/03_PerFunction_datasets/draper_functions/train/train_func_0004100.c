resumeWeakLearners(InputData* pTrainingData)
	{
		if (_resumeShypFileName.empty())
			return 0;

		if (_verbose > 0)
			cout << "Reloading strong hypothesis file <" << _resumeShypFileName << ">.." << flush;


		UnSerialization us;


		for(int stagei=0; stagei < _numIterations; ++stagei )
		{
			us.loadHypotheses(_resumeShypFileName, _foundHypotheses[stagei], pTrainingData, _verbose);

		}

		if (_verbose > 0)
			cout << "Done!" << endl;


		return static_cast<int>( _foundHypotheses.size() );
	}
