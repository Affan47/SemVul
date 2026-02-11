open(std::string filename) const
{
  binifstream *f = new binifstream(filename);

  if(!f) return 0;
  if(f->error()) { delete f; return 0; }


  f->setFlag(binio::BigEndian, false); f->setFlag(binio::FloatIEEE);

  return f;
}
