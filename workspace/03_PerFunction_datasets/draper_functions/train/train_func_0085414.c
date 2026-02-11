LoadSubChunks() {
       #if DEBUG
       std::cout << "List::LoadSubChunks()";
       #endif
        if (!pSubChunks) {
            pSubChunks    = new ChunkList();
            pSubChunksMap = new ChunkMap();
            #if defined(WIN32)
            if (pFile->hFileRead == INVALID_HANDLE_VALUE) return;
            #else
            if (!pFile->hFileRead) return;
            #endif
            unsigned long uiOriginalPos = GetPos();
            SetPos(0);
            while (RemainingBytes() >= CHUNK_HEADER_SIZE) {
                Chunk* ck;
                uint32_t ckid;
                Read(&ckid, 4, 1);
       #if DEBUG
       std::cout << " ckid=" << convertToString(ckid) << std::endl;
       #endif
                if (ckid == CHUNK_ID_LIST) {
                    ck = new RIFF::List(pFile, ulStartPos + ulPos - 4, this);
                    SetPos(ck->GetSize() + LIST_HEADER_SIZE - 4, RIFF::stream_curpos);
                }
                else {
                    ck = new RIFF::Chunk(pFile, ulStartPos + ulPos - 4, this);
                    SetPos(ck->GetSize() + CHUNK_HEADER_SIZE - 4, RIFF::stream_curpos);
                }
                pSubChunks->push_back(ck);
                (*pSubChunksMap)[ckid] = ck;
                if (GetPos() % 2 != 0) SetPos(1, RIFF::stream_curpos);
            }
            SetPos(uiOriginalPos);
        }
    }
