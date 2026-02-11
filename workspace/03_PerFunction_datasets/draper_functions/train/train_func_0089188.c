loadIndexSet( set< int > ind ) {
		int i = 0;

		for (int j = 0; j < this->_rawIndices.size(); j++) this->_rawIndices[j] = -1;

		map<int, int> tmpPointsPerClass;

		for( set< int >::iterator it = ind.begin(); it != ind.end(); it++ ) {
			this->_indirectIndices[i] = *it;
			this->_rawIndices[*it] = i;

			i++;

			const vector<Label>& labels = _pData->getLabels( *it );
			vector<Label>::const_iterator lIt;

			for (lIt = labels.begin(); lIt != labels.end(); ++lIt )
			{
				switch ( this->_pData->getLabelRep() ) {
					case LR_DENSE:
						if ( lIt->y > 0 )
							tmpPointsPerClass[lIt->idx]++;
						break;
					case LR_SPARSE:
						if ( lIt->y > 0 )
							tmpPointsPerClass[lIt->idx]++;
						break;
				}
			}
		}

		_nExamplesPerClass.clear();
		for (int l = 0; l < this->_pData->getNumClasses(); ++l)
			_nExamplesPerClass.push_back( tmpPointsPerClass[l] );


		this->_numExamples = (int)ind.size();

        _subsetAlreadyComputed = false;

		return 0;
	}
