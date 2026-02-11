Ctm3Rotate( Transform3 T, float angle, Point3 *axis )
{
    if(      axis == &TM3_XAXIS ) Ctm3RotateX( T, angle );
    else if( axis == &TM3_YAXIS ) Ctm3RotateY( T, angle );
    else if( axis == &TM3_ZAXIS ) Ctm3RotateZ( T, angle );
    else {
	Transform3 Ta;

	Tm3Rotate( Ta, angle, axis );
	Tm3Concat(Ta, T, T);
    }
}
