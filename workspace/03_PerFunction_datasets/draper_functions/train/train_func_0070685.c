__UpdateWavePoolTable() {
        WavePoolCount = (pSamples) ? pSamples->size() : 0;

        if (pWavePoolTable)   delete[] pWavePoolTable;
        if (pWavePoolTableHi) delete[] pWavePoolTableHi;
        pWavePoolTable   = new uint32_t[WavePoolCount];
        pWavePoolTableHi = new uint32_t[WavePoolCount];
        if (!pSamples) return;

        RIFF::List* wvpl = pRIFF->GetSubList(LIST_TYPE_WVPL);
        uint64_t wvplFileOffset = wvpl->GetFilePos();
        if (b64BitWavePoolOffsets) {
            SampleList::iterator iter = pSamples->begin();
            SampleList::iterator end  = pSamples->end();
            for (int i = 0 ; iter != end ; ++iter, i++) {
                uint64_t _64BitOffset = (*iter)->pWaveList->GetFilePos() - wvplFileOffset - LIST_HEADER_SIZE;
                (*iter)->ulWavePoolOffset = _64BitOffset;
                pWavePoolTableHi[i] = (uint32_t) (_64BitOffset >> 32);
                pWavePoolTable[i]   = (uint32_t) _64BitOffset;
            }
        } else {
            SampleList::iterator iter = pSamples->begin();
            SampleList::iterator end  = pSamples->end();
            for (int i = 0 ; iter != end ; ++iter, i++) {
                uint64_t _64BitOffset = (*iter)->pWaveList->GetFilePos() - wvplFileOffset - LIST_HEADER_SIZE;
                (*iter)->ulWavePoolOffset = _64BitOffset;
                pWavePoolTable[i] = (uint32_t) _64BitOffset;
            }
        }
    }
