destroy(void)
    {
        if (mClosed)
            return;

        mClosed = true;
        mActive = false;

        if (! mIsExternal)
            WindowEventUtilities::_removeRenderWindow(this);

        if (mIsFullScreen)
        {
            mGLSupport->switchMode();
            switchFullScreen(false);
        }
    }
