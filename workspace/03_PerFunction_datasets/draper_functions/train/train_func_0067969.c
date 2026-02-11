constructEMF(int energy, int material, int fuel) {
  stringstream ss;
  ss << energy << " Energy<br>"  << material << " Material<br>" << fuel << " Fuel";
  return  ss.str();
}
