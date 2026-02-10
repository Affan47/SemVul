createCurvedPlane( const String& name, const String& groupName,
        const Plane& plane, Real width, Real height, Real bow, int xsegments, int ysegments,
        bool normals, unsigned short numTexCoordSets, Real xTile, Real yTile, const Vector3& upVector,
            HardwareBuffer::Usage vertexBufferUsage, HardwareBuffer::Usage indexBufferUsage,
            bool vertexShadowBuffer, bool indexShadowBuffer)
    {

        MeshPtr pMesh = createManual(name, groupName, this);

        pMesh->setAutoBuildEdgeLists(false);

        MeshBuildParams params;
        params.type = MBT_CURVED_PLANE;
        params.plane = plane;
        params.width = width;
        params.height = height;
        params.curvature = bow;
        params.xsegments = xsegments;
        params.ysegments = ysegments;
        params.normals = normals;
        params.numTexCoordSets = numTexCoordSets;
        params.xTile = xTile;
        params.yTile = yTile;
        params.upVector = upVector;
        params.vertexBufferUsage = vertexBufferUsage;
        params.indexBufferUsage = indexBufferUsage;
        params.vertexShadowBuffer = vertexShadowBuffer;
        params.indexShadowBuffer = indexShadowBuffer;
        mMeshBuildParams[pMesh.getPointer()] = params;


        pMesh->load();

        return pMesh;

    }
