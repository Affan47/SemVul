rotate(const Quaternion& q, TransformSpace relativeTo)
    {
        switch(relativeTo)
        {
        case TS_PARENT:

            mOrientation = q * mOrientation;
            break;
        case TS_WORLD:

            mOrientation = mOrientation * _getDerivedOrientation().Inverse()
                * q * _getDerivedOrientation();
            break;
        case TS_LOCAL:

            mOrientation = mOrientation * q;
            break;
        }


        mOrientation.normalise();

        needUpdate();
    }
