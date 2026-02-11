setWorkQueue(WorkQueue* queue)
    {
        if (mWorkQueue != queue)
        {

            OGRE_DELETE mWorkQueue;

            mWorkQueue = queue;
            if (mIsInitialised)
                mWorkQueue->startup();

        }
    }
