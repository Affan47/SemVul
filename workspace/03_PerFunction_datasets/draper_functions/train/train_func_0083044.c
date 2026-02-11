processVisibleObject(MovableObject* mo,
        Camera* cam,
        bool onlyShadowCasters,
        VisibleObjectsBoundsInfo* visibleBounds)
    {
        mo->_notifyCurrentCamera(cam);
        if (mo->isVisible())
        {
            bool receiveShadows = getQueueGroup(mo->getRenderQueueGroup())->getShadowsEnabled()
                && mo->getReceivesShadows();

            if (!onlyShadowCasters || mo->getCastShadows())
            {
                mo -> _updateRenderQueue( this );
                if (visibleBounds)
                {
                    visibleBounds->merge(mo->getWorldBoundingBox(true),
                        mo->getWorldBoundingSphere(true), cam,
                        receiveShadows);
                }
            }

            else if (onlyShadowCasters && !mo->getCastShadows() &&
                receiveShadows)
            {
                visibleBounds->mergeNonRenderedButInFrustum(mo->getWorldBoundingBox(true),
                    mo->getWorldBoundingSphere(true), cam);
            }
        }

    }
