mkbitvect(int        brn,
                     branchRec  *brt,
                     branchRec  ***bidxp)
{
    int cnt;
    int i,j;
    branchRec   **bidx;

    cnt = 0;
    for (i=0 ; i<brn ; i++) if (brt[i].dir) cnt++;
    bidx=(cnt!=0)?(branchRec **)malloc(sizeof(branchRec *)*cnt):NULL;
    for (i=j=0 ; i<brn ; i++) {
        if (brt[i].dir) bidx[j++]=brt+i;
    }
    *bidxp=bidx;
    return  j;
}
