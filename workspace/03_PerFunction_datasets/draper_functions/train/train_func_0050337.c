UpdateHistory(const vector< vector< const Word* > >& hypos, vector<size_t>& sourceLengths, vector<size_t>& ref_ids, size_t rank, size_t epoch) {
	for (size_t ref_id = 0; ref_id < hypos.size(); ++ref_id){
	    Phrase phrase(hypos[ref_id]);
	    std::vector< size_t > ngram_counts(BleuScoreState::bleu_order);
	    std::vector< size_t > ngram_matches(BleuScoreState::bleu_order);


	    size_t cur_source_length = sourceLengths[ref_id];
	    size_t hypo_length = hypos[ref_id].size();
	    size_t cur_ref_length = GetClosestRefLength(ref_ids[ref_id], hypo_length);
	    NGrams cur_ref_ngrams = m_refs[ref_ids[ref_id]].second;
	    cerr << "reference length: " << cur_ref_length << endl;


	    GetNgramMatchCounts(phrase, cur_ref_ngrams, ngram_counts, ngram_matches, 0);


	    for (size_t i = 0; i < BleuScoreState::bleu_order; i++) {
	        m_count_history[i] += ngram_counts[i];
	        m_match_history[i] += ngram_matches[i];


	        if (ref_id == hypos.size() - 1) {
	        	m_count_history[i] *= m_historySmoothing;
	        	m_match_history[i] *= m_historySmoothing;
	        }
	    }


	    m_source_length_history += cur_source_length;
	    m_target_length_history += hypos[ref_id].size();
	    m_ref_length_history += cur_ref_length;


	    if (ref_id == hypos.size() - 1) {
	    	cerr << "Rank " << rank << ", epoch " << epoch << " ,source length history: " << m_source_length_history << " --> " << m_source_length_history * m_historySmoothing << endl;
	    	cerr << "Rank " << rank << ", epoch " << epoch << " ,target length history: " << m_target_length_history << " --> " << m_target_length_history * m_historySmoothing << endl;
	    	m_source_length_history *= m_historySmoothing;
	    	m_target_length_history *= m_historySmoothing;
	    	m_ref_length_history *= m_historySmoothing;
	    }
	}
}
