setAutoTracking(bool enabled, SceneNode* const target,
        const Vector3& offset)
    {
        if (enabled)
        {
            assert (target != 0 && "target cannot be a null pointer if tracking is enabled");
            mAutoTrackTarget = target;
            mAutoTrackOffset = offset;
        }
        else
        {
            mAutoTrackTarget = 0;
        }
    }
