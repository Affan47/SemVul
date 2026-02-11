save(StreamSerialiser& ser)
    {
        ser.writeChunkBegin(CHUNK_ID, CHUNK_VERSION);


        ser.write(&mName);

        ser.write(&mAABB);

        ser.write(&mSceneMgr->getTypeName());
        ser.write(&mSceneMgr->getName());

        ser.write(&mStrategy->getName());

        mStrategyData->save(ser);


        saveSubtypeData(ser);

        ser.writeChunkEnd(CHUNK_ID);


        for (PageMap::iterator i = mPages.begin(); i != mPages.end(); ++i)
        {
            i->second->save();
        }


    }
