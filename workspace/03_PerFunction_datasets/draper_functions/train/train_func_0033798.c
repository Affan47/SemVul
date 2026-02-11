makevalues (tr)
     tree  *tr;

{
    nodeptr  p;
    int  i, j;

    for (i = 1; i <= numsp; i++) {
        for (j = 0; j < endsite; j++)
            y[i-1][j] = y[i][patsite[j]];

        p = tr->nodep[i];
        p->tip = &(y[i-1][0]);
    }

}
