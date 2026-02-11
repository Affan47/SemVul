rayTrace(Ray *in,Intersect *output)
{
    Vector W (in->start->x-P1->x, in->start->y-P1->y, in->start->z-P1->z);
    Vector unitD (in->direction);
    unitD.unitize();
    double s,t,threshold=0.5;

    Vector newP (0,0,0);
    Vector newR (0,0,0);

    Vector vT (V->y,-V->x,0);
    Vector dT (in->direction->y, -in->direction->x, 0);
    dT.unitize();

    if(vT.dotProduct(&unitD)==0 || dT.dotProduct(V)==0)
    {
        vT.setVector(0,V->z,-V->y);
        dT.setVector(0,unitD.z,-unitD.y);
        dT.unitize();
        if(vT.dotProduct(&unitD)==0 || dT.dotProduct(V)==0)
        {
            vT.setVector(V->z,0,-V->x);
            dT.setVector(unitD.z,0,-unitD.x);
            dT.unitize();
            if(vT.dotProduct(&unitD)==0 || dT.dotProduct(V)==0)
            {
                output->intersect=false;
                return;
            }
        }

    }

    s= -(vT.dotProduct(&W)/vT.dotProduct(&unitD));
    t= dT.dotProduct(&W)/dT.dotProduct(V);

    if(t>=0 && t<=1)
    {
        newP.setVector(P1->x+t*V->x,P1->y+t*V->y,P1->z+t*V->z);
        newR.setVector(in->start->x+s*unitD.x,in->start->y+s*unitD.y,in->start->z+s*unitD.z);
        if(newP.length(&newR)<=threshold)
            output->reIntersect(color,s,true);
        else
            output->intersect=false;
    }
    else
        output->intersect=false;
}
