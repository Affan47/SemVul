clean_lookup_adv(WordEntry * wi)
  {
    const char * w = wi->word;
    w = get_next(w);
    convert(w,*wi);
    if (!duplicate_flag(w)) wi->adv_ = 0;
  }
