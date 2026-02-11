getStateData( vector<float>& data, const string& , InputData* pData )
	{
	   const int numClasses = pData->getNumClasses();
	   const int numExamples = pData->getNumExamples();


	   data.resize( numClasses + numExamples );
	   int pos = 0;

	   for (int l = 0; l < numClasses; ++l)
		  data[pos++] = _v[l];

	   for (int i = 0; i < numExamples; ++i)
	   {
		  data[pos++] = UCBVHaarSingleStumpLearner::phi(
							_pSelectedFeature->getValue(
							   pData->getValues(i), _selectedConfig ),

						0 );
	   }
	}
