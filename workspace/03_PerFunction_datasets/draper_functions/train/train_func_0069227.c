_notifyCurrentCamera( Camera* cam )
    {
        MovableObject::_notifyCurrentCamera(cam);

        mCurrentCamera = cam;


        mCamQ = mCurrentCamera->getDerivedOrientation();
        mCamPos = mCurrentCamera->getDerivedPosition();
        if (!mWorldSpace)
        {


            mCamQ = mParentNode->convertWorldToLocalOrientation(mCamQ);
            mCamPos = mParentNode->convertWorldToLocalPosition(mCamPos);
        }


        mCamDir = mCamQ * Vector3::NEGATIVE_UNIT_Z;
    }
