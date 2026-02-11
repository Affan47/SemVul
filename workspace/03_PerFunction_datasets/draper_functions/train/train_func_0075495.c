calculateP() {
  Lorentz5Momentum m;
  for(int i = 0; i<_numComp; i++)
    m += _component[i]->momentum();
  m.rescaleMass();
  set5Momentum(m);
}
