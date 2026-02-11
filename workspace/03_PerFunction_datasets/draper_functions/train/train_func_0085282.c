readFile(const std::string& filename)
    {
        FILE* rf = fopen(filename.c_str(), "rb");
        if (!rf)
            { return false; }

        bool result = true;
        uint32 chunkSize = 0;
        uint32 count = 0;
        char chunk[8];
        if (!readChunk(rf, chunk, VMAP_MAGIC, 8)) { result = false; }

        if (result && !readChunk(rf, chunk, "WMOD", 4)) { result = false; }
        if (result && fread(&chunkSize, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (result && fread(&RootWMOID, sizeof(uint32), 1, rf) != 1) { result = false; }


        if (result && readChunk(rf, chunk, "GMOD", 4))
        {


            if (result && fread(&count, sizeof(uint32), 1, rf) != 1) { result = false; }
            if (result) { groupModels.resize(count); }

            for (uint32 i = 0; i < count && result; ++i)
                { result = groupModels[i].readFromFile(rf); }


            if (result && !readChunk(rf, chunk, "GBIH", 4)) { result = false; }
            if (result) { result = groupTree.readFromFile(rf); }
        }

        fclose(rf);
        return result;
    }
