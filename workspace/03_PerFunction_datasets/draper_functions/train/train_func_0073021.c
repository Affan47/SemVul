invert()
{
  std::vector<ftype> hinv( hist.size() );
  hinv[0]             = range_.min();
  hinv[hist.size()-1] = range_.max();
  for ( int i = 1; i < hist.size()-1; i++ ) {
    ftype target = ftype(i)/nranges;
    ftype guess = 0.5 * ( range_.max() + range_.min() );
    ftype step  = 0.5 * ( range_.max() - range_.min() );
    for ( int j = 0; j < 10; j++ ) {
      if ( ordinal( guess ) > target ) guess -= step;
      else                             guess += step;
      step *= 0.5;
    }
    hinv[i] = Util::bound( range_.min(), guess, range_.max() );
  }
  range_ = Range<ftype>( 0.0, 1.0 );
  hist = hinv;
}
