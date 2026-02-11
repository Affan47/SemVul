fine_tune_score() {

    NearMisses::iterator i;

    if (parms->use_typo_analysis) {
      int max = 0;
      unsigned int j;

      CharVector orig_norm, word;
      orig_norm.resize(original.word.size() + 1);
      for (j = 0; j != original.word.size(); ++j)
          orig_norm[j] = parms->ti->to_normalized(original.word[j]);
      orig_norm[j] = 0;
      ParmString orig(orig_norm.data(), j);
      word.resize(max_word_length + 1);

      for (i = scored_near_misses.begin();
	   i != scored_near_misses.end() && i->score <= threshold;
	   ++i)
      {
	for (j = 0; (i->word)[j] != 0; ++j)
	  word[j] = parms->ti->to_normalized((i->word)[j]);
	word[j] = 0;
	int word_score
	  = typo_edit_distance(ParmString(word.data(), j), orig, *parms->ti);
	i->score = weighted_average(i->soundslike_score, word_score);
	if (max < i->score) max = i->score;
      }
      threshold = max;
      for (;i != scored_near_misses.end() && i->score <= threshold; ++i)
	i->score = threshold + 1;

      scored_near_misses.sort();
    }
  }
