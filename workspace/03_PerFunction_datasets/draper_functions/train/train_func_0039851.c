allocate(api::size_t size)
    {
        if (size > BLOCK_SIZE)
        {
            StatsManager::getInstance()->addMemory(size);
            return new char[size];
        }
        if (this->_free_blocks.empty())
        {
            char* n = new char[BLOCK_SIZE];
            this->_blocks.push_back(n);
            StatsManager::getInstance()->addMemory(BLOCK_SIZE);
#ifdef ZHTTPD_DEBUG
            this->_debug[n] = size;
#endif
            return n;
        }
        char* ret = this->_free_blocks.back();
        this->_free_blocks.pop_back();
#ifdef ZHTTPD_DEBUG
        this->_debug[ret] = size;
#endif
        return ret;
    }
