append(CollectorBlock* block) {
        if (m_used == m_capacity) {
            static const size_t maxNumBlocks = ULONG_MAX / sizeof(CollectorBlock*) / GROWTH_FACTOR;
            if (m_capacity > maxNumBlocks)
                CRASH();
            m_capacity = max(MIN_ARRAY_SIZE, m_capacity * GROWTH_FACTOR);
            m_data = static_cast<CollectorBlock **>(fastRealloc(m_data, m_capacity * sizeof(CollectorBlock *)));
        }
        m_data[m_used] = block;
        ++m_used;
    }
