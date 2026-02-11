getNumEntered() {
  unsigned Count = 0;
  for (unsigned i = 0; i != 65536; ++i)
    Count += ShufTab[i].Cost < 100;
  return Count;
}
