CountSubLists(uint32_t ListType) {
        unsigned int result = 0;
        if (!pSubChunks) LoadSubChunks();
        ChunkList::iterator iter = pSubChunks->begin();
        ChunkList::iterator end  = pSubChunks->end();
        while (iter != end) {
            if ((*iter)->GetChunkID() == CHUNK_ID_LIST) {
                List* l = (List*) *iter;
                if (l->GetListType() == ListType) result++;
            }
            iter++;
        }
        return result;
    }
