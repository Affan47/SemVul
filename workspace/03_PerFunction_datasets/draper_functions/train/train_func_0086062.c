makeRotationAboutVector(const Vec3d u, const double angle )
{
	Matrix rx,irx, ry, iry;

    double a = u.x;
    double b = u.y;
    double c = u.z;
	double d = sqrt( b*b + c*c );

    if ( d < EPS ) {
        if ( a < 0 )
            makeRotation( -angle, 'x' );
        else
            makeRotation( angle, 'x' );
        return;
    }

    rx.makeIdentity();
    irx.makeIdentity();
    ry.makeIdentity();
    iry.makeIdentity();

    rx.data[1][1] = c/d;
    rx.data[2][1] = -b/d;
    rx.data[1][2] = b/d;
    rx.data[2][2] = c/d;

    irx.data[1][1] = c/d;
    irx.data[2][1] = b/d;
    irx.data[1][2] = -b/d;
    irx.data[2][2] = c/d;

    ry.data[0][0] = d;
    ry.data[2][0] = -a;
    ry.data[0][2] = a;
    ry.data[2][2] = d;

    iry.data[0][0] = d;
    iry.data[2][0] = a;
    iry.data[0][2] = -a;
    iry.data[2][2] = d;

    makeRotation( angle, 'z' );

    *this=(*this)*ry;
    *this=(*this)*rx;
    *this=iry*(*this);
    *this=irx*(*this);
}
