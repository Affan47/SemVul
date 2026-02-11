build(const ConvexBody& body, bool filterDuplicates)
    {

        mBodyPoints.clear();


        mBodyPoints.reserve(body.getPolygonCount() * 6);


        for (size_t i = 0; i < body.getPolygonCount(); ++i)
        {
            for (size_t j = 0; j < body.getVertexCount(i); ++j)
            {
                const Vector3 &vInsert = body.getVertex(i, j);


                if (filterDuplicates)
                {
                    bool bPresent = false;

                    for(Polygon::VertexList::iterator vit = mBodyPoints.begin();
                        vit != mBodyPoints.end(); ++vit)
                    {
                        const Vector3& v = *vit;

                        if (vInsert.positionEquals(v))
                        {
                            bPresent = true;
                            break;
                        }
                    }

                    if (bPresent == false)
                    {
                        mBodyPoints.push_back(body.getVertex(i, j));
                    }
                }


                else
                {
                    mBodyPoints.push_back(body.getVertex(i, j));
                }
            }
        }


        mAAB = body.getAABB();
    }
