SimplifyRepeat(Regexp* re, int min, int max,
                                       Regexp::ParseFlags f) {

  if (max == -1) {

    if (min == 0)
      return Regexp::Star(re->Incref(), f);


    if (min == 1)
      return Regexp::Plus(re->Incref(), f);


    Regexp* nre = new Regexp(kRegexpConcat, f);
    nre->AllocSub(min);
    VLOG(1) << "Simplify " << min;
    Regexp** nre_subs = nre->sub();
    for (int i = 0; i < min-1; i++)
      nre_subs[i] = re->Incref();
    nre_subs[min-1] = Regexp::Plus(re->Incref(), f);
    return nre;
  }


  if (min == 0 && max == 0)
    return new Regexp(kRegexpEmptyMatch, f);


  if (min == 1 && max == 1)
    return re->Incref();


  Regexp* nre = NULL;
  if (min > 0) {
    nre = new Regexp(kRegexpConcat, f);
    nre->AllocSub(min);
    Regexp** nre_subs = nre->sub();
    for (int i = 0; i < min; i++)
      nre_subs[i] = re->Incref();
  }


  if (max > min) {
    Regexp* suf = Regexp::Quest(re->Incref(), f);
    for (int i = min+1; i < max; i++)
      suf = Regexp::Quest(Concat2(re->Incref(), suf, f), f);
    if (nre == NULL)
      nre = suf;
    else
      nre = Concat2(nre, suf, f);
  }

  if (nre == NULL) {


    LOG(DFATAL) << "Malformed repeat " << re->ToString() << " " << min << " " << max;
    return new Regexp(kRegexpNoMatch, f);
  }

  return nre;
}
