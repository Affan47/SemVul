outputHeader(const NameMap& namemap, bool outputIterations, bool outputTime, bool endline)
	{
        if (outputIterations) {
            _outStream << "t" << OUTPUT_SEPARATOR;
        }

        OutInfIt outputIt;
        long numDatasets = _gTableMap.size();


        for (int i = 0; i < numDatasets; ++i) {
            for (outputIt = _outputList.begin(); outputIt != _outputList.end(); ++outputIt) {
                (*outputIt)->outputHeader(_outStream, namemap);
                _outStream << OUTPUT_SEPARATOR;

                if (outputIt+1 != _outputList.end())
                    _outStream << HEADER_FIELD_LENGTH;
            }
            if (i != numDatasets - 1) {

                separator();
            }
        }

        if (outputTime) {
            _outStream << OUTPUT_SEPARATOR  << "Time";
        }

        if (endline) {
            _outStream << endl;
        }

	}
