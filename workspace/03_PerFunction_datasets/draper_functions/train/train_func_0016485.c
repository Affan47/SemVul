setText(const Str & t_, bool kleine_schrift ,
			int x0 , int x1 ) {
  FontStr t = t_;
  if ((! (mText == t)) || mTextKlein != kleine_schrift
      || x0!=mTextX0 || x1!=mTextX1) {
    mText = t;
    mTextKlein = kleine_schrift;
    mTextX0=x0;
    mTextX1=x1;

    Font * font = Font::gGame;
    font->wordBreak(mText, gric*grx);

    setUpdateAlles();
  }
}
