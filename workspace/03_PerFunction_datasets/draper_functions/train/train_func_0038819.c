writeLodLevel(const Mesh* pMesh)
    {
        if (isLodMixed(pMesh)) {
            LogManager::getSingleton().logMessage("MeshSerializer_v1_8 older mesh format is incompatible with mixed manual/generated Lod levels. Lod levels will not be exported.");
        } else {

            exportedLodCount = pMesh->getNumLodLevels();
            bool manual = pMesh->hasManualLodLevel();

            writeChunkHeader(M_MESH_LOD_LEVEL, calcLodLevelSize(pMesh));


            writeString(compatibleLodStrategyName(pMesh->getLodStrategy()->getName()));

            writeShorts(&exportedLodCount, 1);

            writeBools(&manual, 1);

            pushInnerChunk(mStream);

            for (ushort i = 1; i < exportedLodCount; ++i)
            {
                const MeshLodUsage& usage = pMesh->mMeshLodUsageList[i];
                assert(pMesh->_isManualLodLevel(i) == manual);
                if (manual)
                {
                    writeLodUsageManual(usage);
                }
                else
                {
                    writeLodUsageGenerated(pMesh, usage, i);
                }
            }
            popInnerChunk(mStream);
        }
    }
