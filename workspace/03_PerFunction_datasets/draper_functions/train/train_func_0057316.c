loadHypothesesWithThresholds(const string& shypFileName,
										 vector<BaseLearner*>& weakHypotheses,
                                         vector<AlphaReal>& rejectionThresholds,
										 InputData* pTrainingData, int verbose)
	{

		ifstream inFile(shypFileName.c_str());
		if (!inFile.is_open())
		{
			cerr << "ERROR: Cannot open strong hypothesis file <" << shypFileName << ">!" << endl;
			exit(1);
		}

        rejectionThresholds.resize(0);


		nor_utils::StreamTokenizer st(inFile, "<>\n\r\t");


		if ( !seekSimpleTag(st, "multiboost") )
		{

			cerr << "ERROR: Not a valid MultiBoost Strong Hypothesis file!!" << endl;
			exit(1);
		}


		string algoName = seekAndParseEnclosedValue<string>(st, "algo");


		for ( ; ; )
		{

            if ( seekParamTag(st, "weakhyp") ) {
                double threshold = seekAndParseEnclosedValue<double>(st, "rejecthresh");
                rejectionThresholds.push_back(threshold);
                loadHypothesis(st, weakHypotheses, pTrainingData, verbose);
            }
            else
                break;

		}
		cout << weakHypotheses.size() << endl;

	}
