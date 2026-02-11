checkExistsWithValue(DcmItem *dataset,
                                               const DcmTagKey &key,
                                               const OFFilename &filename)
{

    OFBool result = checkExists(dataset, key, filename);
    if (result)
    {

        result = dataset->tagExistsWithValue(key);
        if (!result && !filename.isEmpty())
        {

            printRequiredAttributeMessage(key, filename, OFTrue );
        }
    }
    return result;
}
