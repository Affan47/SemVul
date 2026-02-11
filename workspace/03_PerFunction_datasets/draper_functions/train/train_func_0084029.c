_autoTrack(void)
    {

        if (mAutoTrackTarget)
        {
            lookAt(mAutoTrackTarget->_getDerivedPosition() + mAutoTrackOffset,
                TS_WORLD, mAutoTrackLocalDirection);

            _update(true, true);
        }
    }
