SkipObjects(int n, OBConversion* pConv)
{
  istream& ifs = *pConv->GetInStream();
  string inchi;
  while(ifs.good() && n)
  {
    inchi = GetInChI(ifs);
    if(inchi.size()>=8)
      --n;
  }
  return ifs.good() ? 1 : -1;
}
