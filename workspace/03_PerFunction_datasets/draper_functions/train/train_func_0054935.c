clone()
    {
        EdgeData* newEdgeData = OGRE_NEW EdgeData();
        newEdgeData->triangles = triangles;
        newEdgeData->triangleFaceNormals = triangleFaceNormals;
        newEdgeData->triangleLightFacings = triangleLightFacings;
        newEdgeData->edgeGroups = edgeGroups;
        newEdgeData->isClosed = isClosed;
        return newEdgeData;
    }
