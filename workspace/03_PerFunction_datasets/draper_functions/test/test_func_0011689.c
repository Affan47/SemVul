NTFArcCenterFromEdgePoints( double x_c0, double y_c0,
                                double x_c1, double y_c1,
                                double x_c2, double y_c2,
                                double *x_center, double *y_center )

{


    if( x_c0 == x_c2 && y_c0 == y_c2 )
    {
        *x_center = (x_c0 + x_c1) * 0.5;
        *y_center = (y_c0 + y_c1) * 0.5;

        return TRUE;
    }


    double m1, x1, y1;

    if( (y_c1 - y_c0) != 0.0 )
        m1 = (x_c0 - x_c1) / (y_c1 - y_c0);
    else
        m1 = 1e+10;

    x1 = (x_c0 + x_c1) * 0.5;
    y1 = (y_c0 + y_c1) * 0.5;


    double m2, x2, y2;

    if( (y_c2 - y_c1) != 0.0 )
        m2 = (x_c1 - x_c2) / (y_c2 - y_c1);
    else
        m2 = 1e+10;

    x2 = (x_c1 + x_c2) * 0.5;
    y2 = (y_c1 + y_c2) * 0.5;


    double      a1, a2, b1, b2, c1, c2;

    a1 = m1;
    a2 = m2;

    b1 = -1.0;
    b2 = -1.0;

    c1 = (y1 - m1*x1);
    c2 = (y2 - m2*x2);


    double      det_inv;

    if( a1*b2 - a2*b1 == 0.0 )
        return FALSE;

    det_inv = 1 / (a1*b2 - a2*b1);

    *x_center = (b1*c2 - b2*c1) * det_inv;
    *y_center = (a2*c1 - a1*c2) * det_inv;

    return TRUE;
}
