initialise(void)
    {
        OverlayContainerList::iterator i, iend;
        iend = m2DElements.end();
        for (i = m2DElements.begin(); i != iend; ++i)
        {
            (*i)->initialise();
        }
        mInitialised = true;
    }
