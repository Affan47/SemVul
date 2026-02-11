zufallsSorte(int wv) {
  CASSERT(mVerteilungSumme[wv]);
  int nummer = Aufnahme::rnd(mVerteilungSumme[wv]);
  int i=blopart_min_sorte;
  for (; nummer>=0; i++)
    nummer-=mSorten[i]->getVerteilung(wv);

  return i-1;
}
