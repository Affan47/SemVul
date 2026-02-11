getViewMatrix(bool ownFrustumOnly) const
    {
        if (ownFrustumOnly)
        {
            return Frustum::getViewMatrix();
        }
        else
        {
            return getViewMatrix();
        }
    }
