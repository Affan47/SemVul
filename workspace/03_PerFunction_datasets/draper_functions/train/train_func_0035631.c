__resolveChunkPath(Chunk* pCk) {
        String sPath;
        for (Chunk* pChunk = pCk; pChunk; pChunk = pChunk->GetParent()) {
            if (pChunk->GetChunkID() == CHUNK_ID_LIST) {
                List* pList = (List*) pChunk;
                sPath = "->'" + pList->GetListTypeString() + "'" + sPath;
            } else {
                sPath = "->'" + pChunk->GetChunkIDString() + "'" + sPath;
            }
        }
        return sPath;
    }
