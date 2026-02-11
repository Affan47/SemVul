intersect( const PlaneBoundedVolume &one, const AxisAlignedBox &two )
    {

        if (two.isNull()) return OUTSIDE;

        if (two.isInfinite()) return INTERSECT;


        Vector3 centre = two.getCenter();

        Vector3 halfSize = two.getHalfSize();


        bool all_inside = true;
        PlaneList::const_iterator i, iend;
        iend = one.planes.end();
        for (i = one.planes.begin(); i != iend; ++i)
        {
            const Plane& plane = *i;

            Plane::Side side = plane.getSide(centre, halfSize);
            if(side == one.outside)
                    return OUTSIDE;
            if(side == Plane::BOTH_SIDE)
                    all_inside = false;
        }

        if ( all_inside )
            return INSIDE;
        else
            return INTERSECT;

    }
