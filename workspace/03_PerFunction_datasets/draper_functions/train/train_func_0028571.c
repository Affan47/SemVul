NewPoly(p,Layer)

Poly *p;
int Layer;
{
    struct p *pp,*Path;
    struct o *NewPointer = NULL;
    int *xy;
    int i,n;

    xy = p->xy;
    Path = pp = alloc(p);
    pp->pX = *xy++;
    pp->pY = *xy++;
    n = p->nvertices - 1;

    for (i = 0; i < n; i++) {
        pp->pSucc = alloc(p);
        pp = pp->pSucc;
        pp->pX = *xy++;
        pp->pY = *xy++;
    }
    pp->pSucc = NULL;

    if (Not CDMakePolygon(Parameters.kpCellDesc,Layer,Path,&NewPointer))
        MallocFailed();
    if (NewPointer) {
        NewPointer->oInfo = SQ_NEW;
        SQInsert(NewPointer);
    }
}
