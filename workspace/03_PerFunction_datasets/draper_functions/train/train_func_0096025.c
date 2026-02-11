SaveBinEntry(BamBinMap& binMap,
				    const uint32_t& saveBin,
				    const uint64_t& saveOffset,
				    const uint64_t& lastOffset)
{

    BamBinMap::iterator binIter = binMap.find(saveBin);


    Chunk newChunk(saveOffset, lastOffset);


    if ( binIter == binMap.end() ) {
        ChunkVector newChunks;
        newChunks.push_back(newChunk);
        binMap.insert( pair<uint32_t, ChunkVector>(saveBin, newChunks));
    }


    else {
        ChunkVector& binChunks = (*binIter).second;
        binChunks.push_back( newChunk );
    }
}
