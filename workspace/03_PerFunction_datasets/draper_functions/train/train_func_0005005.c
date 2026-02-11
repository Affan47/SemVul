AddNgramCountAndMatches(std::vector< size_t >& counts,
																									std::vector< size_t >& matches) {
	for (size_t order = 0; order < BleuScoreState::bleu_order; ++order) {
		m_ngram_counts[order] += counts[order];
		m_ngram_matches[order] += matches[order];
	}
}
