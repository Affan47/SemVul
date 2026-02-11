removeCamera(Camera* c)
    {
        CameraList::iterator i = std::find(mCameraList.begin(), mCameraList.end(), c);
        if (i != mCameraList.end())
        {
            c->removeListener(&mEventRouter);
            mCameraList.erase(i);
        }
    }
