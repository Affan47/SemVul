selftest()
{
  bool ret = true;
  specmap::iterator it = m_IbanSpec.begin();
  for (; it != m_IbanSpec.end(); it++) {
    const Iban& ex = it->second->example;
    int r = check(ex.transmissionForm(), ex.transmissionForm().substr(0,2));
    if (r != OK) {
      std::cout << r << " " << it->second->example << std::endl;
      ret = false;
    }
  }
  return ret;
}
