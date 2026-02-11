generateAndInsertUID(const DcmTagKey& uidKey)
{

    if (dfile==NULL)
        return makeOFCondition(OFM_dcmdata,22,OF_error,"No file loaded yet!");

    OFCondition result;
    char uid[100];
    if (uidKey == DCM_StudyInstanceUID)
        dcmGenerateUniqueIdentifier(uid, SITE_STUDY_UID_ROOT);
    else if (uidKey == DCM_SeriesInstanceUID)
        dcmGenerateUniqueIdentifier(uid, SITE_SERIES_UID_ROOT);
    else if (uidKey == DCM_SOPInstanceUID)
    {
        dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT);

        DcmItem *meta_info = dfile->getMetaInfo();
        if (meta_info)
        {
            delete meta_info->remove(DCM_MediaStorageSOPInstanceUID);
        }
    }
    else return EC_IllegalCall;
    result = dset->putAndInsertString(uidKey, uid);
    return result;
}
