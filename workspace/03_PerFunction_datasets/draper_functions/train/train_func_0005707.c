getVisibility( const AxisAlignedBox &bound )
{


    if ( bound.isNull() )
        return NONE;


    Vector3 centre = bound.getCenter();

    Vector3 halfSize = bound.getHalfSize();

    bool all_inside = true;

    for ( int plane = 0; plane < 6; ++plane )
    {


        if (plane == FRUSTUM_PLANE_FAR && mFarDist == 0)
            continue;


        Plane::Side side = getFrustumPlane(plane).getSide(centre, halfSize);
        if(side == Plane::NEGATIVE_SIDE) return NONE;

        if(side == Plane::BOTH_SIDE)
                all_inside = false;
    }

    if ( all_inside )
        return FULL;
    else
        return PARTIAL;

}
