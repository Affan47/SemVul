initCollapseCosts( LodData* data )
    {
        data->mCollapseCostHeap.clear();
        LodData::VertexList::iterator it = data->mVertexList.begin();
        LodData::VertexList::iterator itEnd = data->mVertexList.end();
        for (; it != itEnd; it++) {
            if (!it->edges.empty()) {
                initVertexCollapseCost(data, &*it);
            } else {
#if OGRE_DEBUG_MODE
                LogManager::getSingleton().stream() << "In " << data->mMeshName << " never used vertex found with ID: " << data->mCollapseCostHeap.size() << ". "
                    << "Vertex position: ("
                    << it->position.x << ", "
                    << it->position.y << ", "
                    << it->position.z << ") "
                    << "It will be excluded from Lod level calculations.";
#endif
            }
        }
    }
