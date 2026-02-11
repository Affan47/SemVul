DoVerticalBar() {
  MaybeConcatString(-1, NoParseFlags);
  DoConcatenation();


  Regexp* r1;
  Regexp* r2;
  if ((r1 = stacktop_) != NULL &&
      (r2 = stacktop_->down_) != NULL &&
      r2->op() == kVerticalBar) {


    Regexp* r3;
    if ((r1->op() == kRegexpLiteral ||
         r1->op() == kRegexpCharClass ||
         r1->op() == kRegexpAnyChar) &&
        (r3 = r2->down_) != NULL) {
      Rune rune;
      switch (r3->op()) {
        case kRegexpLiteral:
          rune = r3->rune_;
          r3->op_ = kRegexpCharClass;
          r3->cc_ = NULL;
          r3->ccb_ = new CharClassBuilder;
          AddLiteral(r3->ccb_, rune, r3->parse_flags_ & Regexp::FoldCase);

        case kRegexpCharClass:
          if (r1->op() == kRegexpLiteral)
            AddLiteral(r3->ccb_, r1->rune_,
                       r1->parse_flags_ & Regexp::FoldCase);
          else if (r1->op() == kRegexpCharClass)
            r3->ccb_->AddCharClass(r1->ccb_);
          if (r1->op() == kRegexpAnyChar || r3->ccb_->full()) {
            delete r3->ccb_;
            r3->ccb_ = NULL;
            r3->op_ = kRegexpAnyChar;
          }

        case kRegexpAnyChar:

          stacktop_ = r2;
          r1->Decref();
          return true;
        default:
          break;
      }
    }


    r1->down_ = r2->down_;
    r2->down_ = r1;
    stacktop_ = r2;
    return true;
  }
  return PushSimpleOp(kVerticalBar);
}
