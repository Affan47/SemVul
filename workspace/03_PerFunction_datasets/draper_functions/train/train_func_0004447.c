updateNodeHomeZone( PCZSceneNode * pczsn, bool allowBackTouches )
    {

        PCZone * newHomeZone = pczsn->getHomeZone();


        Portal* portal;
        PortalList::iterator pi, piend;
        piend = mPortals.end();
        for (pi = mPortals.begin(); pi != piend; pi++)
        {
            portal = *pi;

            Portal::PortalIntersectResult pir = portal->intersects(pczsn);
            switch (pir)
            {
            default:
            case Portal::NO_INTERSECT:
            case Portal::INTERSECT_NO_CROSS:
                break;
            case Portal::INTERSECT_BACK_NO_CROSS:
                if (allowBackTouches)
                {

                    if (portal->getTargetZone() != this &&
                        portal->getTargetZone() != pczsn->getHomeZone())
                    {

                        pczsn->setHomeZone(portal->getTargetZone());

                        newHomeZone = portal->getTargetZone()->updateNodeHomeZone(pczsn, false);
                    }
                }
                break;
            case Portal::INTERSECT_CROSS:

                if (portal->getTargetZone() != this &&
                    portal->getTargetZone() != pczsn->getHomeZone())
                {

                    pczsn->setHomeZone(portal->getTargetZone());

                    newHomeZone = portal->getTargetZone()->updateNodeHomeZone(pczsn, true);
                }
                break;
            }
        }


        return newHomeZone;

    }
