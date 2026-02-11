reposition(int left, int top)
    {
        if (mClosed || ! mIsTopLevel)
            return;

        XMoveWindow(mGLSupport->getXDisplay(), mWindow, left, top);
    }
