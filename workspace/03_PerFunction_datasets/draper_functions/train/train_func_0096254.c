setRelativeValues()
{
    dVector3 anchor;
    dJointGetHinge2Anchor(this, anchor);
    setAnchors( this, anchor[0], anchor[1], anchor[2], anchor1, anchor2 );

    dVector3 axis;

    if ( node[0].body )
    {
        dJointGetHinge2Axis1(this, axis);
        setAxes( this, axis[0],axis[1],axis[2], axis1, NULL );
    }

    if ( node[0].body )
    {
        dJointGetHinge2Axis2(this, axis);
        setAxes( this, axis[0],axis[1],axis[2], NULL, axis2 );
    }

    dVector3 ax1, ax2;
    getAxisInfo( ax1, ax2, axis, s0, c0 );

    makeV1andV2();
}
