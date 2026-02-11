importMesh(DataStreamPtr& stream, Mesh* pMesh, MeshSerializerListener *listener)
    {

        determineEndianness(stream);

#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        enableValidation();
#endif

        readFileHeader(stream);
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);

        while(!stream->eof())
        {
            switch (streamID)
            {
            case M_MESH:
                readMesh(stream, pMesh, listener);
                break;
            }

            streamID = readChunk(stream);
        }
        popInnerChunk(stream);
    }
