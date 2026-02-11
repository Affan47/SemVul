deallocateScratch(void* ptr)
    {
            OGRE_LOCK_MUTEX(mScratchMutex);


        uint32 bufferPos = 0;
        GLScratchBufferAlloc* pLast = 0;
        while (bufferPos < SCRATCH_POOL_SIZE)
        {
            GLScratchBufferAlloc* pCurrent = (GLScratchBufferAlloc*)(mScratchBufferPool + bufferPos);


            if ((mScratchBufferPool + bufferPos + sizeof(GLScratchBufferAlloc))
                == ptr)
            {

                pCurrent->free = 1;


                if (pLast && pLast->free)
                {

                    bufferPos -= (pLast->size + (uint32)sizeof(GLScratchBufferAlloc));

                    pLast->size += pCurrent->size + sizeof(GLScratchBufferAlloc);
                    pCurrent = pLast;
                }


                uint32 offset = bufferPos + pCurrent->size + (uint32)sizeof(GLScratchBufferAlloc);
                if (offset < SCRATCH_POOL_SIZE)
                {
                    GLScratchBufferAlloc* pNext = (GLScratchBufferAlloc*)(
                        mScratchBufferPool + offset);
                    if (pNext->free)
                    {
                        pCurrent->size += pNext->size + sizeof(GLScratchBufferAlloc);
                    }
                }


                return;
            }

            bufferPos += (uint32)sizeof(GLScratchBufferAlloc) + pCurrent->size;
            pLast = pCurrent;

        }


        assert (false && "Memory deallocation error");


    }
