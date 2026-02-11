adjustMergingIndices( int offset,
                                          const MergingIndexList::Iterator &it )
{
    MergingIndexList::Iterator mergingIt = it;
    MergingIndexList::Iterator mergingEnd = mergingIndices.end();

    for (; mergingIt != mergingEnd; ++mergingIt )
        (*mergingIt).value += offset;

    index += offset;
}
