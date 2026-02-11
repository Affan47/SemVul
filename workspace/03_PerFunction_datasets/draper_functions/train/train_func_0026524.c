widenRectByVector(const Vector3& vec, const Rect& inRect,
        Real minHeight, Real maxHeight, Rect& outRect)
    {

        outRect = inRect;

        Plane p;
        switch(getAlignment())
        {
        case ALIGN_X_Y:
            p.redefine(Vector3::UNIT_Z, Vector3(0, 0, vec.z < 0.0 ? minHeight : maxHeight));
            break;
        case ALIGN_X_Z:
            p.redefine(Vector3::UNIT_Y, Vector3(0, vec.y < 0.0 ? minHeight : maxHeight, 0));
            break;
        case ALIGN_Y_Z:
            p.redefine(Vector3::UNIT_X, Vector3(vec.x < 0.0 ? minHeight : maxHeight, 0, 0));
            break;
        }
        float verticalVal = vec.dotProduct(p.normal);

        if (Math::RealEqual(verticalVal, 0.0))
            return;

        Vector3 corners[4];
        Real startHeight = verticalVal < 0.0 ? maxHeight : minHeight;
        getPoint(inRect.left, inRect.top, startHeight, &corners[0]);
        getPoint(inRect.right-1, inRect.top, startHeight, &corners[1]);
        getPoint(inRect.left, inRect.bottom-1, startHeight, &corners[2]);
        getPoint(inRect.right-1, inRect.bottom-1, startHeight, &corners[3]);

        for (int i = 0; i < 4; ++i)
        {
            Ray ray(corners[i] + mPos, vec);
            std::pair<bool, Real> rayHit = ray.intersects(p);
            if(rayHit.first)
            {
                Vector3 pt = ray.getPoint(rayHit.second);

                Vector3 terrainHitPos;
                getTerrainPosition(pt, &terrainHitPos);


                Rect mergeRect(
                    (long)(terrainHitPos.x * (mSize - 1)),
                    (long)(terrainHitPos.y * (mSize - 1)),
                    (long)(terrainHitPos.x * (float)(mSize - 1) + 0.5) + 1,
                    (long)(terrainHitPos.y * (float)(mSize - 1) + 0.5) + 1
                    );
                outRect.merge(mergeRect);
            }
        }

    }
