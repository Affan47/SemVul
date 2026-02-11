isNoOp() const
    {
        AutoMutex lock(m_mutex);

        if(luts[0].empty() || luts[1].empty() || luts[2].empty())
            throw Exception("Cannot compute noOp of invalid Lut1D");

        if(!m_cacheID.empty())
            return m_isNoOp;

        finalize();

        return m_isNoOp;
    }
