DeleteStuff()
{
  delete thermal_;
  delete gray256_;
  delete gray16_;
  delete rainbow_;
  delete redblue16_;
  delete classic8_;
  delete topo256_;
  delete default_;
  delete userdefined_;
  std::vector<GRA_color*>::const_iterator end = namedColors_.end();
  for( std::vector<GRA_color*>::const_iterator i=namedColors_.begin(); i!=end; ++i )
    delete *i;
}
