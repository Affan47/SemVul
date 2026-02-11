_notifyVertexBufferDestroyed(HardwareVertexBuffer* buf)
    {
            OGRE_LOCK_MUTEX(mVertexBuffersMutex);

        VertexBufferList::iterator i = mVertexBuffers.find(buf);
        if (i != mVertexBuffers.end())
        {

            mVertexBuffers.erase(i);
            _forceReleaseBufferCopies(buf);
        }
    }
