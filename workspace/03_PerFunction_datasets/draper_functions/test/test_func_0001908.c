Grow()
{
#ifdef DEBUG
    Check();
#endif

    if ( maxNormSquared > se_maxGridSize )
        return;

    base = base.Turn(-4,0);
    maxNormSquared=base.NormSquared();

    a->ClearWall();
    b->ClearWall();
    c->ClearWall();

    ePoint *newA=tNEW(ePoint) (base.Turn(1,0));
    ePoint *newB=tNEW(ePoint) (base.Turn(-.5,.87));
    ePoint *newC=tNEW(ePoint) (base.Turn(-.5,-.87));

    eHalfEdge *newa=tNEW(eHalfEdge) (newB,newC,tNEW(eWall(this)));
    eHalfEdge *newb=tNEW(eHalfEdge) (newC,newA,tNEW(eWall(this)));
    eHalfEdge *newc=tNEW(eHalfEdge) (newA,newB,tNEW(eWall(this)));

    eHalfEdge *AnewB=tNEW(eHalfEdge) (A,newB,NULL);
    eHalfEdge *AnewC=tNEW(eHalfEdge) (A,newC,NULL);
    eHalfEdge *BnewA=tNEW(eHalfEdge) (B,newA,NULL);
    eHalfEdge *BnewC=tNEW(eHalfEdge) (B,newC,NULL);
    eHalfEdge *CnewA=tNEW(eHalfEdge) (C,newA,NULL);
    eHalfEdge *CnewB=tNEW(eHalfEdge) (C,newB,NULL);

    AddFaceAll(tNEW(eFace) (a->other,BnewA,CnewA->other));
    AddFaceAll(tNEW(eFace) (b->other,CnewB,AnewB->other));
    AddFaceAll(tNEW(eFace) (c->other,AnewC,BnewC->other));

    AddFaceAll(tNEW(eFace) (newa,AnewC->other,AnewB));
    AddFaceAll(tNEW(eFace) (newb,BnewA->other,BnewC));
    AddFaceAll(tNEW(eFace) (newc,CnewB->other,CnewA));

    a=newa;
    b=newb;
    c=newc;

    A=newA;
    B=newB;
    C=newC;

    a->other->next = c->other;
    a->other->prev = b->other;
    b->other->next = a->other;
    b->other->prev = c->other;
    c->other->next = b->other;
    c->other->prev = a->other;

#ifdef DEBUG
    Check();
#endif
}
