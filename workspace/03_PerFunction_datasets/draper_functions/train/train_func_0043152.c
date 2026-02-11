setAutoTracking(bool enabled, SceneNode* const target,
        const Vector3& localDirectionVector,
        const Vector3& offset)
    {
        if (enabled)
        {
            mAutoTrackTarget = target;
            mAutoTrackOffset = offset;
            mAutoTrackLocalDirection = localDirectionVector;
        }
        else
        {
            mAutoTrackTarget = 0;
        }
        if (mCreator)
            mCreator->_notifyAutotrackingSceneNode(this, enabled);
    }
