visitRenderables(
        Renderable::Visitor* visitor, bool debugRenderables)
    {
        GeometryBucketList::iterator i, iend;
        iend =  mGeometryBucketList.end();
        for (i = mGeometryBucketList.begin(); i != iend; ++i)
        {
            (*i)->visitRenderables(visitor, debugRenderables);
        }

    }
