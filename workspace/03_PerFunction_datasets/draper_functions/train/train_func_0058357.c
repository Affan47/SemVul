getLump(int lumpType)
    {
        if (mLumpStart)
        {

#if OGRE_ENDIAN == OGRE_ENDIAN_BIG

            SwapFourBytes ((uint32*)&mHeader->lumps[lumpType].offset);
#endif
            return (unsigned char*)mHeader + mHeader->lumps[lumpType].offset;
        }
        else
        {
            return 0;
        }
    }
