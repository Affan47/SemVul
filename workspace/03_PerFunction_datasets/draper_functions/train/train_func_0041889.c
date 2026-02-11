dJointGetPUAngles( dJointID j, dReal *angle1, dReal *angle2 )
{
    dxJointUniversal* joint = ( dxJointUniversal* ) j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, PU );
    if ( joint->flags & dJOINT_REVERSE )
        joint->getAngles( angle2, angle1 );
    else
        joint->getAngles( angle1, angle2 );
}
