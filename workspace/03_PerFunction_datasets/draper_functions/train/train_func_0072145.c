Affiche(void)
{
  printf("sh=%p nbPt=%i nbAr=%i\n", this, static_cast<int>(_pts.size()), static_cast<int>(_aretes.size()));
  for (unsigned int i=0; i<_pts.size(); i++) {
    printf("pt %i : x=(%f %f) dI=%i dO=%i\n",i, _pts[i].x[0], _pts[i].x[1], _pts[i].dI, _pts[i].dO);
  }
  for (unsigned int i=0; i<_aretes.size(); i++) {
    printf("ar %i : dx=(%f %f) st=%i en=%i\n",i, _aretes[i].dx[0], _aretes[i].dx[1], _aretes[i].st, _aretes[i].en);
  }
}
