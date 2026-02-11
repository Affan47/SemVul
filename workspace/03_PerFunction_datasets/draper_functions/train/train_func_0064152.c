knot(int n,int c,int x[])

{
    int nplusc,nplus2,i;

    nplusc = n + c;
    nplus2 = n + 2;

    x[1] = 0;
    for (i = 2; i <= nplusc; i++){
        if ( (i > c) && (i < nplus2) )
            x[i] = x[i-1] + 1;
        else
            x[i] = x[i-1];
    }
}
