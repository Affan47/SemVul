save(ofstream& outputStream, int numTabs)
	{

		FeaturewiseLearner::save(outputStream, numTabs);


		outputStream << Serialization::standardTag("sigSlope", _sigmoidSlope, numTabs) << endl;
		outputStream << Serialization::standardTag("sigOffset", _sigmoidOffset, numTabs) << endl;

	}
