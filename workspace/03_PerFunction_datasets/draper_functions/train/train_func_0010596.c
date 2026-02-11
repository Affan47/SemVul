_boundsDirty(void)
    {

        if( !mBoundsDirty && !mKeepStatic )
            mCreator->_addDirtyBatch( this );
        mBoundsDirty = true;
    }
