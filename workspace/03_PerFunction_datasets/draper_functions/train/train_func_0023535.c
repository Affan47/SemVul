GetSubList(uint32_t ListType) {
        #if DEBUG
        std::cout << "List::GetSubList(uint32_t)" << std::endl;
        #endif
        if (!pSubChunks) LoadSubChunks();
        ChunkList::iterator iter = pSubChunks->begin();
        ChunkList::iterator end  = pSubChunks->end();
        while (iter != end) {
            if ((*iter)->GetChunkID() == CHUNK_ID_LIST) {
                List* l = (List*) *iter;
                if (l->GetListType() == ListType) return l;
            }
            iter++;
        }
        return NULL;
    }
