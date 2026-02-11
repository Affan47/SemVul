calcEdgeListLodSize(const EdgeData* edgeData, bool isManual)
    {
        size_t size = MSTREAM_OVERHEAD_SIZE;


        size += sizeof(uint16);


        size += sizeof(bool);
        if (!isManual)
        {

            size += sizeof(bool);

            size += sizeof(uint32);

            size += sizeof(uint32);

            size_t triSize = 0;


            triSize += sizeof(uint32) * 8
                    + sizeof(float) * 4;

            size += triSize * edgeData->triangles.size();

            for (EdgeData::EdgeGroupList::const_iterator gi = edgeData->edgeGroups.begin();
                gi != edgeData->edgeGroups.end(); ++gi)
            {
                const EdgeData::EdgeGroup& edgeGroup = *gi;
                size += calcEdgeGroupSize(edgeGroup);
            }

        }

        return size;
    }
