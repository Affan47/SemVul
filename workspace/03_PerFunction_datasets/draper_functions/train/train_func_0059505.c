sinfo_new_hat_deriv1( float * xdat, float * parlist,
                      float * dervs )
{

    if ( xdat[0] <= parlist[0] )
    {
        dervs[0] = 0. ;
        dervs[1] = 0. ;
        dervs[2] = 1. ;
        dervs[3] = 0. ;
        dervs[4] = 0. ;
    }
    else if ( xdat[0] > parlist[0] && xdat[0] <= parlist[0] + slopewidth )
    {
        dervs[0] = ( parlist[2] - parlist[4] ) / slopewidth ;
        dervs[1] = 0. ;
        dervs[2] = (( parlist[0] - xdat[0] ) / slopewidth ) + 1. ;
        dervs[3] = 0. ;
        dervs[4] = ( xdat[0] - parlist[0] ) / slopewidth ;
    }
    else if ( xdat[0] > parlist[0] + slopewidth && xdat[0] <=
              parlist[1] - slopewidth )
    {
        dervs[0] = 0. ;
        dervs[1] = 0. ;
        dervs[2] = 0. ;
        dervs[3] = 0. ;
        dervs[4] = 1. ;
    }
    else if ( xdat[0] > parlist[1] - slopewidth && xdat[0] <= parlist[1] )
    {
        dervs[0] = 0. ;
        dervs[1] = ( parlist[4] - parlist[3] ) / slopewidth ;
        dervs[2] = 0. ;
        dervs[3] = (( xdat[0] - parlist[1] ) / slopewidth ) + 1. ;
        dervs[4] = ( parlist[1] - xdat[0] ) / slopewidth ;
    }
    else if ( xdat[0] > parlist[1] )
    {
        dervs[0] = 0. ;
        dervs[1] = 0. ;
        dervs[2] = 0. ;
        dervs[3] = 1. ;
        dervs[4] = 0. ;
    }
}
