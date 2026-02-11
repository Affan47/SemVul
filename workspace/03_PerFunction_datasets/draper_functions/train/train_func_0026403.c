BiCubicLength( Geometry_t *Geometry,int UnotV )
{
    double *X,*Y,*Z,EofL,Length;

    int i,j=0;

    X = Geometry->BiCubic->PolyFactors[0];
    Y = Geometry->BiCubic->PolyFactors[1];
    Z = Geometry->BiCubic->PolyFactors[2];

    Length = 0.0;
    for( j=0; j<4; j++ )
    for( i=0; i<N_Integ1d; i++ )
    {
        if ( UnotV )
            EofL = BiCubicEofL(U_Integ1d[i],j/3.0,X,Y,Z,1);
        else
            EofL = BiCubicEofL(j/3.0,U_Integ1d[i],X,Y,Z,0);

        Length += S_Integ1d[i]*EofL;
    }

    return Length;
}
