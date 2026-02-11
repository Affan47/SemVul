writeCardinalProperty(const char *p, Integer n)
{
  stringstream t;
  t<<n<<endl;
  writeProperty(p,t.str());
}
