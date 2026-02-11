change_nearest_vertex(Path,X,Y,NewX,NewY,Type)


struct p *Path;
int X,Y,NewX,NewY;
int Type;
{
    double dx,dy,d,mind;
    struct p *p;
    int i,indx = 0;

    mind = 1e30;
    for (p = Path,i = 0; p; p = p->pSucc,i++) {
        dx = p->pX - X;
        dy = p->pY - Y;
        d = dx*dx + dy*dy;
        if (d < mind) {
            mind = d;
            indx = i;
        }
    }
    if (indx == 0 && Type == CDPOLYGON) {
        for (p = Path; p && p->pSucc; p = p->pSucc) ;
        if (Path->pX == p->pX And Path->pY == p->pY) {
            if (Parameters.kpStretchType != STR_TB)
                p->pX += NewX - X;
            if (Parameters.kpStretchType != STR_RL)
                p->pY += NewY - Y;
        }
    }
    for (p = Path, i = 0; i < indx; p = p->pSucc,i++) ;
    if (Parameters.kpStretchType != STR_TB)
        p->pX += NewX - X;
    if (Parameters.kpStretchType != STR_RL)
        p->pY += NewY - Y;
}
