getOffsetFromChunkStart() const
    {
        checkStream(false, false, false);

        if (mChunkStack.empty())
        {
            return 0;
        }
        else
        {
            size_t pos = mStream->tell();
            size_t diff = pos - mChunkStack.back()->offset;
            if(diff >= CHUNK_HEADER_SIZE)
                return diff - CHUNK_HEADER_SIZE;
            else
                return 0;

        }

    }
