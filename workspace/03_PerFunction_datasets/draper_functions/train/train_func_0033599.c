out_poly(Path, po)


struct p *Path;
Poly *po;
{
    int i;
    struct p *pp;
    Poly p1;
    int *xy, *bxy;

    if (!po) {
        for (i = 0, pp = Path; pp; i++,pp = pp->pSucc) ;
        p1.nvertices = i;
        xy = (int*) tmalloc(i*2*sizeof(int));
        p1.xy = xy;
        for (pp = Path; pp; pp = pp->pSucc) {
            *xy++ = pp->pX;
            *xy++ = pp->pY;
        }
    }
    else
        p1 = *po;

    if (p1.nvertices > MAXSTRMCOORDS/2) {
        OutPrompt("Breaking polygon with too many vertices.");
        break_poly(&p1);
    }
    else {
        xy = p1.xy;
        bxy = STRMBoundary->bnd_xy;
        for (i = 0; i < p1.nvertices; i++) {
            *bxy++ = LONGSCALE(*xy++);
            *bxy++ = LONGSCALE(*xy++);
        }
        if (i < 4) {

            *bxy++ = STRMBoundary->bnd_xy[0];
            *bxy++ = STRMBoundary->bnd_xy[1];
            i++;
        }
        STRMBoundary->bnd_ncoord = i;
        bndry(STRMBoundary);
    }
    if (!po)
        free(p1.xy);
}
