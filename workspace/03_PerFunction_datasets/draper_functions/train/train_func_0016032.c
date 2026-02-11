configuration() const
{
  store_econfiguration = 1;
  Vector<String> conf;
  configuration(conf);
  store_econfiguration = 0;


  return cp_unargvec(conf);
}
