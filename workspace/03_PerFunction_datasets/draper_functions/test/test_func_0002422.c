importLodConfig(Ogre::LodConfig* config, DataStreamPtr& stream)
    {
        mStream = stream;
        mLodConfig = config;


        determineEndianness(mStream);


        readFileHeader(mStream);

        pushInnerChunk(mStream);
        while (!mStream->eof())
        {
            unsigned short streamID = readChunk(mStream);
            switch (streamID)
            {
            case LCCID_LOD_CONFIG:
                readLodConfig();
                break;
            default:
                backpedalChunkHeader(mStream);
                popInnerChunk(mStream);
                return;
            }
        }
        popInnerChunk(mStream);
    }
