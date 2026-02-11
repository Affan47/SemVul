prepare(StreamSerialiser& stream)
    {

        for (LodLevelList::iterator i = mLodLevels.begin(); i != mLodLevels.end(); ++i)
        {
            LodLevel* ll = *i;


            stream.read(&ll->calcMaxHeightDelta);
            ll->maxHeightDelta = ll->calcMaxHeightDelta;
            ll->lastCFactor = 0;
        }

        if (!isLeaf())
        {
            for (int i = 0; i < 4; ++i)
                mChildren[i]->prepare(stream);
        }


        if (!mParent)
        {
            Rect rect;
            rect.top = mOffsetY; rect.bottom = mBoundaryY;
            rect.left = mOffsetX; rect.right = mBoundaryX;
            postDeltaCalculation(rect);
        }
    }
