contains(int id1) const {

  bool found1 = false;
  for (int i = 0; i < nProd; ++i) if (prod[i] == id1) found1 = true;
  return found1;

}
