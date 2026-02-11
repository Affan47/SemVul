updateGeometryWithoutNotifyNeighbours()
    {
        if (!mDirtyGeometryRect.isNull())
        {
            mQuadTree->updateVertexData(true, false, mDirtyGeometryRect, false);
            mDirtyGeometryRect.setNull();
        }
    }
