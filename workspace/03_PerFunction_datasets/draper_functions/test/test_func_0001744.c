to_soundslike_temp(const WordEntry & sw) {
      char * sl = (char *)buffer.alloc_temp(sw.word_size + 1);
      temp_end = lang->LangImpl::to_soundslike(sl, sw.word, sw.word_size, sw.word_info);
      if (temp_end == 0) return sw.word;
      else return sl;}
