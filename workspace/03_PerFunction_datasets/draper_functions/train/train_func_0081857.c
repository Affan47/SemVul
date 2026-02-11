insertMediaSOPUID( DcmMetaInfo &metaInfo )
{
    OFCondition l_error = EC_Normal;
    DcmTag medSOPClassTag( DCM_MediaStorageSOPClassUID );
    DcmUniqueIdentifier *mediaStorageSOPClassUID = new DcmUniqueIdentifier( medSOPClassTag );
    const char* valueUID = UID_MediaStorageDirectoryStorage;
    mediaStorageSOPClassUID->putString( valueUID );
    metaInfo.insert( mediaStorageSOPClassUID, OFTrue );
    return l_error;
}
