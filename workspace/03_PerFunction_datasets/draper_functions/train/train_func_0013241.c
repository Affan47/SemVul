ReleaseChunkData() {
        if (pChunkData) {
            delete[] pChunkData;
            pChunkData = NULL;
        }
    }
