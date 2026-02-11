contains(int id1, int id2, int id3) const {

  bool found1 = false;
  bool found2 = false;
  bool found3 = false;
  for (int i = 0; i < nProd; ++i) {
    if (!found1 && prod[i] == id1) {found1 = true; continue;}
    if (!found2 && prod[i] == id2) {found2 = true; continue;}
    if (!found3 && prod[i] == id3) {found3 = true; continue;}
  }
  return found1 && found2 && found3;

}
