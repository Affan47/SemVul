vect(string keyIn, vector<double> nowIn) {
  if (isVect(keyIn)) {
    Vect& vectNow = vects[toLower(keyIn)];
    vectNow.valNow.clear();
    for(vector<double>::iterator now = nowIn.begin();
	now != nowIn.end(); now++) {
      if (vectNow.hasMin && *now < vectNow.valMin)
	vectNow.valNow.push_back(vectNow.valMin);
      else if (vectNow.hasMax && *now > vectNow.valMax)
	vectNow.valNow.push_back(vectNow.valMax);
      else vectNow.valNow.push_back(*now);
    }
  }
}
