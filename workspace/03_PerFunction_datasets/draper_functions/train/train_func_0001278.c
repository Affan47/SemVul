insertRepresentationEntry(
    DcmRepresentationEntry * repEntry)
{
    DcmRepresentationListIterator insertedEntry;
    DcmRepresentationListIterator result;
    if (findRepresentationEntry(*repEntry, result).good())
    {

        if (repEntry != *result)
        {
          insertedEntry = repList.insert(result, repEntry);


          delete *result;
          repList.erase(result);
        }
    }
    else
        insertedEntry = repList.insert(result,repEntry);
    return insertedEntry;
}
