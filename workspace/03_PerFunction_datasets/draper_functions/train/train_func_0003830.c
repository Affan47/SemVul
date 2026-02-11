resetBounds(const Rect& rect)
    {
        if (rectContainsNode(rect))
        {
            mAABB.setNull();
            mBoundingRadius = 0;

            if (!isLeaf())
            {
                for (int i = 0; i < 4; ++i)
                    mChildren[i]->resetBounds(rect);
            }


        }
    }
