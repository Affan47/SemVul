Build(Internal::BamReaderPrivate* reader) {


    if ( reader == 0 )
        return false;


    BgzfStream* bgzfStream = reader->Stream();
    if ( bgzfStream == 0 || !bgzfStream->IsOpen )
        return false;


    if ( !reader->Rewind() ) return false;


    const int numReferences = reader->GetReferenceCount();
    m_indexData.clear();
    m_hasFullDataCache = false;
    SetReferenceCount(numReferences);


    int32_t currentBlockCount      = 0;
    int64_t currentAlignmentOffset = bgzfStream->Tell();
    int32_t blockRefId             = 0;
    int32_t blockMaxEndPosition    = 0;
    int64_t blockStartOffset       = currentAlignmentOffset;
    int32_t blockStartPosition     = -1;


    BamAlignment al;
    while ( reader->LoadNextAlignment(al) ) {


        if ( currentBlockCount > 0 && al.RefID != blockRefId ) {


            BamToolsIndexEntry entry(blockMaxEndPosition, blockStartOffset, blockStartPosition);
            SaveOffsetEntry(blockRefId, entry);


            currentBlockCount   = 0;
            blockMaxEndPosition = al.GetEndPosition();
            blockStartOffset    = currentAlignmentOffset;
        }


        if ( currentBlockCount == 0 ) {
            blockRefId         = al.RefID;
            blockStartPosition = al.Position;
        }


        ++currentBlockCount;


        int32_t alignmentEndPosition = al.GetEndPosition();
        if ( alignmentEndPosition > blockMaxEndPosition )
            blockMaxEndPosition = alignmentEndPosition;


        if ( currentBlockCount == m_blockSize ) {
            BamToolsIndexEntry entry(blockMaxEndPosition, blockStartOffset, blockStartPosition);
            SaveOffsetEntry(blockRefId, entry);
            blockStartOffset  = bgzfStream->Tell();
            currentBlockCount = 0;
        }


        currentAlignmentOffset = bgzfStream->Tell();
    }


    BamToolsIndexEntry entry(blockMaxEndPosition, blockStartOffset, blockStartPosition);
    SaveOffsetEntry(blockRefId, entry);


    m_hasFullDataCache = true;


    return reader->Rewind();
}
