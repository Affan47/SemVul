drawIsland(Island *f) {
    int i,j,k;
    Fragment *q;

#ifdef TEST
    double score;
    score=f->score;
#endif

    for(q=f->fragments;q;q=q->next) {
        for(i=q->beginX,j=q->beginY,k=0;k<q->length;k++,i++,j++) {

#ifdef TEST
            if(
               i>=0&&i<TELEN&&j>=0&&j<TELEN
               ) {
                TE[i][j]=score;

            }
#endif

        }
    }

}
