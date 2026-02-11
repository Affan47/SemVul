serialize(const Vector3 &from, const Vector3 &to, float voxelWidth, Real maxClampedAbsoluteDensity, const String &file)
    {

        DataStreamPtr stream = Root::getSingleton().createFileStream(file);
#if OGRE_NO_ZIP_ARCHIVE == 0
        DataStreamPtr compressStream(OGRE_NEW DeflateStream(file, stream));
        StreamSerialiser ser(compressStream);
#else
        StreamSerialiser ser(stream);
#endif
        ser.writeChunkBegin(VOLUME_CHUNK_ID, VOLUME_CHUNK_VERSION);


        ser.write(&from);
        ser.write(&to);
        ser.write<float>(&voxelWidth);
        Vector3 diagonal = to - from;
        size_t gridWidth = (size_t)(diagonal.x / voxelWidth);
        size_t gridHeight = (size_t)(diagonal.y / voxelWidth);
        size_t gridDepth = (size_t)(diagonal.z / voxelWidth);
        ser.write<size_t>(&gridWidth);
        ser.write<size_t>(&gridHeight);
        ser.write<size_t>(&gridDepth);


        Vector3 pos;
        Real realVal;
        size_t x;
        size_t y;
        uint16 buffer[SERIALIZATION_CHUNK_SIZE];
        size_t bufferI = 0;
        for (size_t z = 0; z < gridDepth; ++z)
        {
            for (x = 0; x < gridWidth; ++x)
            {
                for (y = 0; y < gridHeight; ++y)
                {
                    pos.x = x * voxelWidth + from.x;
                    pos.y = y * voxelWidth + from.y;
                    pos.z = z * voxelWidth + from.z;
                    realVal = Math::Clamp<Real>(getValue(pos), -maxClampedAbsoluteDensity, maxClampedAbsoluteDensity);
                    buffer[bufferI] = Bitwise::floatToHalf(realVal);
                    bufferI++;
                    if (bufferI == SERIALIZATION_CHUNK_SIZE)
                    {
                        ser.write<uint16>(buffer, SERIALIZATION_CHUNK_SIZE);
                        bufferI = 0;
                    }
                }
            }
        }
        if (bufferI > 0)
        {
            ser.write<uint16>(buffer, bufferI);
        }
        ser.writeChunkEnd(VOLUME_CHUNK_ID);

    }
