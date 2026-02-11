PushLiteral(Rune r) {

  if ((flags_ & FoldCase) && CycleFoldRune(r) != r) {
    Regexp* re = new Regexp(kRegexpCharClass, flags_ & ~FoldCase);
    re->ccb_ = new CharClassBuilder;
    Rune r1 = r;
    do {
      if (!(flags_ & NeverNL) || r != '\n') {
        re->ccb_->AddRange(r, r);
      }
      r = CycleFoldRune(r);
    } while (r != r1);
    re->ccb_->RemoveAbove(rune_max_);
    return PushRegexp(re);
  }


  if ((flags_ & NeverNL) && r == '\n')
    return PushRegexp(new Regexp(kRegexpNoMatch, flags_));


  if (MaybeConcatString(r, flags_))
    return true;

  Regexp* re = new Regexp(kRegexpLiteral, flags_);
  re->rune_ = r;
  return PushRegexp(re);
}
