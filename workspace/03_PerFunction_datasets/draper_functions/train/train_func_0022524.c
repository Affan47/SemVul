calcDirectionAndRadius(void) const
{
    Vector3 radiusVector;
    Vector3 side1, side2;


    Vector3 min(Math::POS_INFINITY, Math::POS_INFINITY, Math::POS_INFINITY);
    Vector3 max(Math::NEG_INFINITY, Math::NEG_INFINITY, Math::NEG_INFINITY);

    switch (mType)
    {
    default:
    case PORTAL_TYPE_QUAD:

        side1 = mCorners[1] - mCorners[0];
        side2 = mCorners[2] - mCorners[0];
        mDirection = side1.crossProduct(side2);
        mDirection.normalise();

        mLocalCP = Vector3::ZERO;
        for (int i=0;i<4;i++)
        {
            mLocalCP += mCorners[i];

            min.makeFloor(mCorners[i]);
            max.makeCeil(mCorners[i]);
        }
        mLocalCP *= 0.25f;

        radiusVector = mCorners[0] - mLocalCP;
        mRadius = radiusVector.length();
        break;
    case PORTAL_TYPE_AABB:


        mLocalCP = Vector3::ZERO;
        for (int i=0;i<2;i++)
        {
            mLocalCP += mCorners[i];
        }
        mLocalCP *= 0.5f;


        radiusVector = mCorners[0] - mLocalCP;
        mRadius = radiusVector.length();

        min = mCorners[0];
        max = mCorners[1];
        break;
    case PORTAL_TYPE_SPHERE:


        mLocalCP = mCorners[0];

        radiusVector = mCorners[1] - mLocalCP;
        mRadius = radiusVector.length();

        min = mDerivedCP - mRadius;
        max = mDerivedCP + mRadius;
        break;
    }
    mDerivedSphere.setRadius(mRadius);
    mLocalPortalAAB.setExtents(min, max);

    mLocalsUpToDate = true;
}
