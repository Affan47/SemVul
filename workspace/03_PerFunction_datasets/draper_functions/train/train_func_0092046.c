computeAndOutput(ostream& outStream, InputData* pData,
											 map<InputData*, table>& gTableMap,
											 map<InputData*, table>& marginsTableMap,
											 map<InputData*, AlphaReal>& alphaSums,
											 BaseLearner* pWeakHypothesis)
    {
        const int numExamples = pData->getNumExamples();

        table& g = gTableMap[pData];

        vector<Label>::const_iterator lIt;

        int numErrors = 0;

        for (int i = 0; i < numExamples; ++i)
        {
            const vector<Label>& labels = pData->getLabels(i);


            AlphaReal maxNegClass = -numeric_limits<AlphaReal>::max();

            AlphaReal maxPosClass = -numeric_limits<AlphaReal>::max();

            for ( lIt = labels.begin(); lIt != labels.end(); ++lIt )
            {

                if ( lIt->y < 0 && g[i][lIt->idx] > maxNegClass )
                    maxNegClass = g[i][lIt->idx];


                if ( lIt->y > 0 && g[i][lIt->idx] > maxPosClass )
                    maxPosClass = g[i][lIt->idx];
            }


            if (maxPosClass <= maxNegClass)
                ++numErrors;
        }


        outStream  << (AlphaReal)(numErrors)/(AlphaReal)(numExamples);

    }
