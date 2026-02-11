UpdateChunks() {

        RIFF::List* _3gri = pFile->pRIFF->GetSubList(LIST_TYPE_3GRI);
        if (!_3gri) {
            _3gri = pFile->pRIFF->AddSubList(LIST_TYPE_3GRI);
            pFile->pRIFF->MoveSubChunk(_3gri, pFile->pRIFF->GetSubChunk(CHUNK_ID_PTBL));
        }
        RIFF::List* _3gnl = _3gri->GetSubList(LIST_TYPE_3GNL);
        if (!_3gnl) _3gnl = _3gri->AddSubList(LIST_TYPE_3GNL);

        if (!pNameChunk && pFile->pVersion && pFile->pVersion->major == 3) {

            for (RIFF::Chunk* ck = _3gnl->GetFirstSubChunk() ; ck ; ck = _3gnl->GetNextSubChunk()) {
                if (strcmp(static_cast<char*>(ck->LoadChunkData()), "") == 0) {
                    pNameChunk = ck;
                    break;
                }
            }
        }


        ::SaveString(CHUNK_ID_3GNM, pNameChunk, _3gnl, Name, String("Unnamed Group"), true, 64);
    }
