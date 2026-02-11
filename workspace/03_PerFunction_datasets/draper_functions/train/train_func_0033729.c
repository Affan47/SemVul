isVisible(const PortalBase* portal) const
    {

        if (!portal->getEnabled()) return false;


        if (mActiveCullingPlanes.empty())
        {
            return true;
        }


        PCPlaneList::const_iterator pit = mActiveCullingPlanes.begin();
        while ( pit != mActiveCullingPlanes.end() )
        {
            PCPlane * plane = *pit;
            if (plane->getPortal() == portal)
            {
                return false;
            }
            pit++;
        }

        if (portal->getType() == PortalBase::PORTAL_TYPE_AABB)
        {
            AxisAlignedBox aabb;
            aabb.setExtents(portal->getDerivedCorner(0), portal->getDerivedCorner(1));
            return isVisible(aabb);
        }
        else if (portal->getType() == PortalBase::PORTAL_TYPE_SPHERE)
        {
            return isVisible(portal->getDerivedSphere());
        }


        if (portal->getTypeFlags() == PortalFactory::FACTORY_TYPE_FLAG)
        {

            Vector3 frustumToPortal = portal->getDerivedCP() - mOrigin;
            Vector3 portalDirection = portal->getDerivedDirection();
            Real dotProduct = frustumToPortal.dotProduct(portalDirection);
            if ( dotProduct > 0 )
            {

                return false;
            }
        }


        bool visible_flag;


        if (mUseOriginPlane)
        {

            visible_flag = false;

            for (int corner = 0; corner < 4; corner++)
            {
                Plane::Side side = mOriginPlane.getSide(portal->getDerivedCorner(corner));
                if (side != Plane::NEGATIVE_SIDE)
                {
                    visible_flag = true;
                    break;
                }
            }


            if (visible_flag == false)
            {

                return false;
            }
        }


        pit = mActiveCullingPlanes.begin();
        while ( pit != mActiveCullingPlanes.end() )
        {
            PCPlane * plane = *pit;

            visible_flag = false;

            for (int corner = 0; corner < 4; corner++)
            {
                Plane::Side side =plane->getSide(portal->getDerivedCorner(corner));
                if (side != Plane::NEGATIVE_SIDE)
                {
                    visible_flag = true;
                    break;
                }
            }


            if (visible_flag == false)
            {

                return false;
            }
            pit++;
        }


        return true;

    }
