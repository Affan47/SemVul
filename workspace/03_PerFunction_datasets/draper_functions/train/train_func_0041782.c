allocateSpace( size_t numPolygons, size_t numVertices )
    {
        reset();


        for ( size_t iPoly = 0; iPoly < numPolygons; ++iPoly )
        {
            Polygon *poly = allocatePolygon();

            for ( size_t iVertex = 0; iVertex < numVertices; ++iVertex )
            {
                poly->insertVertex( Vector3::ZERO );
            }

            mPolygons.push_back( poly );
        }
    }
