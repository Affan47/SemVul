map_bspline_poly(pointf **pbs_p, int **pbs_n, int *pbs_poly_n, int n, pointf* p1, pointf* p2)
{
    int i = 0, nump = 0, last = 2*n-1;

    for ( ; i < *pbs_poly_n; i++)
        nump += (*pbs_n)[i];

    (*pbs_poly_n)++;
    *pbs_n = grealloc(*pbs_n, (*pbs_poly_n) * sizeof(int));
    (*pbs_n)[i] = 2*n;
    *pbs_p = grealloc(*pbs_p, (nump + 2*n) * sizeof(pointf));

    for (i = 0; i < n; i++) {
        (*pbs_p)[nump+i] = p1[i];
        (*pbs_p)[nump+last-i] = p2[i];
    }
#if (DEBUG==2)
    psmapOutput (*pbs_p + nump, last+1);
#endif
}
