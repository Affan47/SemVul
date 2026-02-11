LoadGroups() {
        if (!pGroups) pGroups = new std::list<Group*>;

        RIFF::List* lst3gri = pRIFF->GetSubList(LIST_TYPE_3GRI);
        if (lst3gri) {
            RIFF::List* lst3gnl = lst3gri->GetSubList(LIST_TYPE_3GNL);
            if (lst3gnl) {
                RIFF::Chunk* ck = lst3gnl->GetFirstSubChunk();
                while (ck) {
                    if (ck->GetChunkID() == CHUNK_ID_3GNM) {
                        if (pVersion && pVersion->major == 3 &&
                            strcmp(static_cast<char*>(ck->LoadChunkData()), "") == 0) break;

                        pGroups->push_back(new Group(this, ck));
                    }
                    ck = lst3gnl->GetNextSubChunk();
                }
            }
        }

        if (!pGroups->size()) {
            Group* pGroup = new Group(this, NULL);
            pGroup->Name = "Default Group";
            pGroups->push_back(pGroup);
        }
    }
