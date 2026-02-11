LoadBin(ReferenceIndex& refEntry, bool saveData) {

    size_t elementsRead = 0;


    uint32_t binId;
    elementsRead += fread(&binId, sizeof(binId), 1, m_indexStream);
    if ( m_isBigEndian ) SwapEndian_32(binId);


    ChunkVector chunks;
    bool chunksOk = LoadChunks(chunks, saveData);


    if ( chunksOk && saveData )
        refEntry.Bins.insert(pair<uint32_t, ChunkVector>(binId, chunks));


    return ( (elementsRead == 1) && chunksOk );
}
