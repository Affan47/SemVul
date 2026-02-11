cleanupicons()
{
  Icon *i, **icons;
  int nicons=0, maxicons=16;

  if((icons=calloc(maxicons, sizeof(Icon*)))) {
    for(i=scr->icons; i; i=i->next)
      if(i->window) {
	if(nicons>=maxicons)
	  if(!(icons=realloc(icons, sizeof(Icon*)*(maxicons<<=1))))
	    return;
	icons[nicons]=i;
	i->x+=i->width>>1;
	nicons++;
      }
    if(nicons) {
      int i0=0, i, x=5, y=scr->bh+4, w, mw=0;
      qsort(icons, nicons, sizeof(*icons),
	    (int (*)(const void *, const void *))cmp_iconpos);
      for(i=0; i<nicons; i++) {
	if(i>i0 && y+icons[i]->height>scr->height-4-scr->lh) {
	  placeicons(icons+i0, i-i0, x, mw);
	  x+=mw+5;
	  y=scr->bh+4;
	  mw=0;
	  i0=i;
	}
	icons[i]->y=y;
	w=icons[i]->width;
	if(icons[i]->mapped && icons[i]->labelwidth>w)
	  w=icons[i]->labelwidth;
	if(w>mw)
	  mw=w;
	y+=icons[i]->height+4+scr->lh;
      }
      placeicons(icons+i0, nicons-i0, x, mw);
    }
    free(icons);
  }
}
