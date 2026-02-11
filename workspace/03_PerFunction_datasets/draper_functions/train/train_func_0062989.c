checkExistsWithStringValue(DcmItem *dataset,
                                                     const DcmTagKey &key,
                                                     const OFString &value,
                                                     const OFFilename &filename)
{

    OFBool result = checkExists(dataset, key, filename);
    if (result)
    {
        OFString str;

        dataset->findAndGetOFStringArray(key, str);

        result = compare(str, value);
        if (!result && !filename.isEmpty())
        {

            printUnexpectedValueMessage(key, filename);
        }
    }
    return result;
}
