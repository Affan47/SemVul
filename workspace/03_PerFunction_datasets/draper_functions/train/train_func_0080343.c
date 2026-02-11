fillBuffer( Ogre::MeshPtr mesh )
    {
        meshName = mesh->getName();
        boundingSphereRadius = mesh->getBoundingSphereRadius();
        bool sharedVerticesAdded = false;
        unsigned short submeshCount = mesh->getNumSubMeshes();
        submesh.resize(submeshCount);
        for (unsigned short i = 0; i < submeshCount; i++) {
            const SubMesh* ogresubmesh = mesh->getSubMesh(i);
            LodInputBuffer::Submesh& outsubmesh = submesh[i];
            outsubmesh.indexBuffer.fillBuffer(ogresubmesh->indexData);
            outsubmesh.useSharedVertexBuffer = ogresubmesh->useSharedVertices;
            if (!outsubmesh.useSharedVertexBuffer) {
                outsubmesh.vertexBuffer.fillBuffer(ogresubmesh->vertexData);
            } else if (!sharedVerticesAdded) {
                sharedVerticesAdded = true;
                sharedVertexBuffer.fillBuffer(mesh->sharedVertexData);
            }
        }
    }
