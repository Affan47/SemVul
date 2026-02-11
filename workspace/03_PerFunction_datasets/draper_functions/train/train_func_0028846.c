pal_set(Palette *p, int i, Argb *c) { if (i<256 && i>=0) { p->cols[i]=*c; if (i>=p->size) p->size=i+1; } }
