RayHitBiCubic
  (
   Geometry_t *Geometry,double FX,double FY,double FZ,double DX,double DY,double DZ,double L
  )
{
    double A0,B0,C0,D0,A1,B1,C1,D1,RayPlanes[2][4];

    if ( !RayHitBBox(&Geometry->BBox,FX,FY,FZ,DX,DY,DZ) ) return FALSE;

    if ( ABS(DX)>ABS(DY) && ABS(DX)>ABS(DZ) )
    {
        B0 = 1;
        C0 = 2;
        A0 = (-C0*DZ - B0*DY)/DX;
        B1 = 2;
        C1 = 3;
        A1 = (-B1*DY - C1*DZ)/DX;
    } else if ( ABS(DY)>ABS(DX) && ABS(DY)>ABS(DZ) )
    {
        A0 = 1;
        C0 = 2;
        B0 = (-C0*DZ - A0*DX)/DY;
        A1 = 3;
        C1 = 1;
        B1 = (-A1*DX - C1*DZ)/DY;
    } else
    {
        A0 = 1;
        B0 = 2;
        C0 = (-B0*DY - A0*DX)/DZ;
        A1 = 3;
        B1 = 1;
        C1 = (-A1*DX - B1*DY)/DZ;
    }

    D0 = -A0*FX - B0*FY - C0*FZ;
    D1 = -A1*FX - B1*FY - C1*FZ;

    RayPlanes[0][0] = A0;
    RayPlanes[0][1] = B0;
    RayPlanes[0][2] = C0;
    RayPlanes[0][3] = D0;

    RayPlanes[1][0] = A1;
    RayPlanes[1][1] = B1;
    RayPlanes[1][2] = C1;
    RayPlanes[1][3] = D1;

    return SolveRayBiCubic( Geometry,RayPlanes,FX,FY,FZ,DX,DY,DZ,L,0 );
}
