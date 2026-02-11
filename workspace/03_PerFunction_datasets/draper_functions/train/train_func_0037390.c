write(const void* buf, size_t count)
    {
        size_t written = 0;
        if (isWriteable() && mFStream)
        {
            mFStream->write(static_cast<const char*>(buf), static_cast<std::streamsize>(count));
            written = count;
        }
        return written;
    }
