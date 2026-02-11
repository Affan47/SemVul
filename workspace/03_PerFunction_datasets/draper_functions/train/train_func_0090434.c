add_nearmiss(char * word, unsigned word_size,
                             WordInfo word_info,
                             const char * sl,
                             int w_score, int sl_score,
                             bool count, WordEntry * rl)
  {
    if (word_size * parms->edit_distance_weights.max >= 0x8000)
      return;

    if (w_score < 0) w_score = LARGE_NUM;
    if (sl_score < 0) sl_score = LARGE_NUM;
    if (!sp->have_soundslike) {
      if (w_score >= LARGE_NUM)       w_score = sl_score;
      else if (sl_score >= LARGE_NUM) sl_score = w_score;
    }

    near_misses.push_front(ScoreWordSound());
    ScoreWordSound & d = near_misses.front();
    d.word = word;
    d.soundslike = sl;


    if (parms->use_typo_analysis) {
      unsigned int l = word_size;
      if (l > max_word_length) max_word_length = l;
    }

    if (!(word_info & ALL_CLEAN)) {
      d.word_clean = (char *)buffer.alloc(word_size + 1);
      lang->LangImpl::to_clean((char *)d.word_clean, word);
    } else {
      d.word_clean = d.word;
    }

    if (!sp->have_soundslike && !d.soundslike)
      d.soundslike = d.word_clean;

    d.word_score       = w_score;
    d.soundslike_score = sl_score;
    d.count = count;
    d.repl_list = rl;
  }
