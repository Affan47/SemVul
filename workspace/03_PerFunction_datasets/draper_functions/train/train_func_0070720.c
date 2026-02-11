learn(const std::vector<std::string>& change)
{
    logger << INFO << "learn(\"" << ngram_to_string(change) << "\")" << endl;

    if (wanna_learn) {


	try
	{
	    db->beginTransaction();

	    for (size_t curr_cardinality = 1;
		 curr_cardinality < cardinality + 1;
		 curr_cardinality++) {

		logger << DEBUG << "Learning for n-gram cardinality: " << curr_cardinality << endl;


		for (std::vector<std::string>::const_reverse_iterator idx = change.rbegin();
		     idx != change.rend();
		     idx++)
		{
		    Ngram ngram;


		    for (std::vector<std::string>::const_reverse_iterator inner_idx = idx;
			 inner_idx != change.rend() && ngram.size() < curr_cardinality;
			 inner_idx++)
		    {
			ngram.insert(ngram.begin(), *inner_idx);
		    }

		    logger << DEBUG << "After filling n-gram with change tokens: " << ngram_to_string(ngram) << endl;


		    for (int tk_idx = 1;
			 ngram.size() < curr_cardinality;
			 tk_idx++)
		    {


			std::string extra_token = contextTracker->getExtraTokenToLearn(tk_idx, change);
			logger << DEBUG << "Adding extra token: " << extra_token << endl;
			ngram.insert(ngram.begin(), extra_token);
		    }


		    logger << INFO << "Considering to learn ngram: |";
		    for (size_t j = 0; j < ngram.size(); j++) {
			logger << INFO << ngram[j] << '|';
		    }
		    logger << INFO << endl;

		    if (ngram.end() == find(ngram.begin(), ngram.end(), "")) {

			db->incrementNgramCount(ngram);
			check_learn_consistency(ngram);
			logger << INFO << "Learnt ngram" << endl;
		    } else {
			logger << INFO << "Discarded ngram" << endl;
		    }
		}
	    }

            db->endTransaction();
            logger << INFO << "Committed learning update to database" << endl;
	}
	catch (SqliteDatabaseConnector::SqliteDatabaseConnectorException& ex)
	{
	    db->rollbackTransaction();
	    logger << ERROR << "Rolling back learning update : " << ex.what() << endl;
	    throw;
	}
    }

    logger << DEBUG << "end learn()" << endl;
}
