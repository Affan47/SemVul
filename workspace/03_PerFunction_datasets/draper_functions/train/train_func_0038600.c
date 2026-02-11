resize(uint width, uint height)
    {
        if (mClosed)
            return;

        if(mWidth == width && mHeight == height)
            return;

        if(width != 0 && height != 0)
        {
            if (!mIsExternal)
            {
                XResizeWindow(mGLSupport->getXDisplay(), mWindow, width, height);
            }
            else
            {
                mWidth = width;
                mHeight = height;

                for (ViewportList::iterator it = mViewportList.begin(); it != mViewportList.end(); ++it)
                    (*it).second->_updateDimensions();
            }
        }
    }
