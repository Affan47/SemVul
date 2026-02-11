_fcalc(void)
{
    int modif;
    int i,j;

    modif=0;

    for(i=1;i<pointcnt-2;i++) {
	for(j=i+1;j<pointcnt-1;j++) {
	    if(dist[chain[i-1]][chain[i]]+dist[chain[j]][chain[j+1]]
	       >dist[chain[i-1]][chain[j]]+dist[chain[i]][chain[j+1]]
	       +tolerance) {
		reverse(i,j); modif=1;
	    }
	}
    }

    for(i=1;i<pointcnt-1;i++) {
	double dd;
	int th;
	th=chain[i];
	dd=dist[chain[i-1]][th]+dist[th][chain[i+1]]
	  -dist[chain[i-1]][chain[i+1]];
	for(j=0;j<pointcnt-1;j++) {
	    if(j==i || j==i-1) continue;
	    if(dd>dist[chain[j]][th]+dist[chain[j+1]][th]
	       -dist[chain[j]][chain[j+1]]+tolerance) {
		reinsert(i,j+1); modif=1;
	    }
	}
    }
    for(i=0;i<pointcnt;i++) shpath[shortcnt][i]=chain[i];
    shortcnt+=modif; return modif;
}
