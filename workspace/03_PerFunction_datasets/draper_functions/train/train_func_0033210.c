ScoreNbestList(const string& scoreFile, const string& featureFile) {
	vector<string> scoreFiles;
	vector<string> featureFiles;
	scoreFiles.push_back(scoreFile);
	featureFiles.push_back(featureFile);

	vector<FeatureDataIterator> featureDataIters;
	vector<ScoreDataIterator> scoreDataIters;
	for (size_t i = 0; i < featureFiles.size(); ++i) {
		featureDataIters.push_back(FeatureDataIterator(featureFiles[i]));
	    scoreDataIters.push_back(ScoreDataIterator(scoreFiles[i]));
	}

	vector<pair<size_t,size_t> > hypotheses;
	if (featureDataIters[0] == FeatureDataIterator::end()) {
		cerr << "Error: at the end of feature data iterator" << endl;
		exit(1);
	}
	for (size_t i = 0; i < featureFiles.size(); ++i) {
		if (featureDataIters[i] == FeatureDataIterator::end()) {
			cerr << "Error: Feature file " << i << " ended prematurely" << endl;
	        exit(1);
		}
		if (scoreDataIters[i] == ScoreDataIterator::end()) {
			cerr << "Error: Score file " << i << " ended prematurely" << endl;
	        exit(1);
	    }
		if (featureDataIters[i]->size() != scoreDataIters[i]->size()) {
			cerr << "Error: features and scores have different size" << endl;
	        exit(1);
		}
		for (size_t j = 0; j < featureDataIters[i]->size(); ++j) {
			hypotheses.push_back(pair<size_t,size_t>(i,j));
	    }
	}


	vector<float> bleuScores;
	for (size_t i=0; i < hypotheses.size(); ++i) {
		pair<size_t,size_t> translation = hypotheses[i];
		float bleu = smoothedSentenceBleu(scoreDataIters[translation.first]->operator[](translation.second));
		bleuScores.push_back(bleu);
	}
	return bleuScores;
}
