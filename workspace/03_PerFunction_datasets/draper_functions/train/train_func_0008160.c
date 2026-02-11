createOffsetTable(const DcmOffsetList &offsetList)
{
    OFCondition result = EC_Normal;

    size_t numEntries = offsetList.size();
    if (numEntries > 0)
    {
        Uint32 current = 0;
        Uint32 *array = new Uint32[numEntries];
        if (array)
        {
            DCMDATA_DEBUG("DcmPixelItem: creating offset table with " << numEntries << " entries");
            OFListConstIterator(Uint32) first = offsetList.begin();
            OFListConstIterator(Uint32) last = offsetList.end();
            unsigned long idx = 0;
            while ((first != last) && result.good())
            {

                if (current & 1)
                {
                    DCMDATA_WARN("DcmPixelItem: odd frame size (" << current << ") found for frame #"
                        << (idx + 1) << ", cannot create offset table");
                    result = EC_InvalidBasicOffsetTable;
                } else {
                    array[idx++] = current;
                    current += *first;
                    ++first;
                }
            }
            if (result.good())
            {
                result = swapIfNecessary(EBO_LittleEndian, gLocalByteOrder, array, OFstatic_cast(Uint32, numEntries * sizeof(Uint32)), sizeof(Uint32));
                if (result.good())
                    result = putUint8Array(OFreinterpret_cast(Uint8 *, array), OFstatic_cast(unsigned long, numEntries * sizeof(Uint32)));
            }
            delete[] array;
        } else
            result = EC_MemoryExhausted;
    }
    return result;
}
