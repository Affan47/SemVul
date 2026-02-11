new_taso_morph(Taso *a, Taso *b, float v) {
  Taso *d=getmem(sizeof(Taso));
  int i;
  if (a->ac<b->ac) { Taso *t=b; b=a; a=t; v=1-v; }

  d->ac=a->ac;
  d->al=getmem(sizeof(Alue*)*d->ac);
  for (i=0; i<b->ac; i++) d->al[i]=new_alue_morph(a->al[i], b->al[i], v);
  for (; i<d->ac; i++) d->al[i]=new_alue_fade(a->al[i], b->al[b->ac-1], v);
  return d;
}
