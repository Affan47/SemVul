CountSubChunks() {
        if (!pSubChunks) LoadSubChunks();
        return pSubChunks->size();
    }
