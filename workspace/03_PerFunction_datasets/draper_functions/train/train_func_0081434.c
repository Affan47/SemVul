dJointGetPRPositionRate( dJointID j )
{
    dxJointPR* joint = ( dxJointPR* ) j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, PR );

    dVector3 ax1;
    dMULTIPLY0_331( ax1, joint->node[0].body->posr.R, joint->axisP1 );

    if ( joint->node[1].body )
    {
        dVector3 lv2;
        dBodyGetRelPointVel( joint->node[1].body, joint->anchor2[0], joint->anchor2[1], joint->anchor2[2], lv2 );
        return dDOT( ax1, joint->node[0].body->lvel ) - dDOT( ax1, lv2 );
    }
    else
    {
        dReal rate = dDOT( ax1, joint->node[0].body->lvel );
        return ( (joint->flags & dJOINT_REVERSE) ? -rate : rate);
    }
}
