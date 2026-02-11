removeItem(const OFString &studyUID,
                                                    const OFString &seriesUID,
                                                    const OFString &instanceUID)
{

    OFCondition result = gotoItem(studyUID, seriesUID, instanceUID);

    if (result.good())
        result = removeItem();
    return result;
}
