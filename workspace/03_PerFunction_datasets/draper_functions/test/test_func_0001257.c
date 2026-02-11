release_cfblocks(void) {

    register U16B i,j,d;

    do {
	do if (++nrel==NUMCON) nrel=0; while (nb[nrel]==NIL);
	for (i=0;i<=usp;++i) if ((cps[i]&0x7fff)==nrel) break;
    } while (i<=usp);
    for (i=nb[nrel],d=fa[nrel];i!=NIL;i=nb[i]) if (fa[i]<d) d=fa[i];
    ++d;
    if (fa[nrel]<d) {
	for (i=nb[nrel];fa[i]<d && nb[i]!=NIL;i=nb[i]);
	fa[nrel]=fa[i];
	fc[nrel]=fc[i];
	j=nb[i];
	nb[i]=fcfbl;
	fcfbl=nb[nrel];
	if ((nb[nrel]=j)==NIL) {
	    cc[nrel]=0;
	    fe[nrel]=(ft[nrel]=fa[nrel])<ESCTH?1:0;
	    return;
	}
    }
    fe[nrel]=(ft[nrel]=fa[nrel]/=d)<ESCTH?1:0;
    cc[nrel]=0;
    for (j=nrel,i=nb[j];i!=NIL;) {
	if (fa[i]<d) {
	    nb[j]=nb[i];
	    nb[i]=fcfbl;
	    fcfbl=i;
	    i=nb[j];
	}
	else {
	    ++cc[nrel];
	    ft[nrel]+=fa[i]/=d;
	    if (fa[i]<ESCTH) fe[nrel]++;
	    j=i;
	    i=nb[i];
	}
    }
}
