CopyStuff( GRA_legend const &rhs )
{
  xlo_ = rhs.xlo_;
  ylo_ = rhs.ylo_;
  xhi_ = rhs.xhi_;
  yhi_ = rhs.yhi_;
  xLineStart_ = rhs.xLineStart_;
  xLineEnd_ = rhs.xLineEnd_;
  xLabel_ = rhs.xLabel_;

  std::size_t size = rhs.entries_.size();
  for( std::size_t i=0; i<size; ++i )
    entries_[i] = new GRA_legendEntry(*rhs.entries_[i]);

  frame_ = new GRA_rectangle( *rhs.frame_ );
  title_ = new GRA_drawableText( *rhs.title_ );

  popup_ = rhs.popup_;
}
