bk_extract_boot_record(VolInfo* volInfo, const char* destPathAndName,
                           unsigned destFilePerms)
{
    int srcFile;
    bool srcFileWasOpened;
    int destFile;
    int rc;

    if(volInfo->bootMediaType == BOOT_MEDIA_NONE)
        return BKERROR_EXTRACT_ABSENT_BOOT_RECORD;

    if(volInfo->bootMediaType != BOOT_MEDIA_NO_EMULATION &&
       volInfo->bootMediaType != BOOT_MEDIA_1_2_FLOPPY &&
       volInfo->bootMediaType != BOOT_MEDIA_1_44_FLOPPY &&
       volInfo->bootMediaType != BOOT_MEDIA_2_88_FLOPPY)
    {
        return BKERROR_EXTRACT_UNKNOWN_BOOT_MEDIA;
    }


    if(volInfo->bootRecordIsVisible)

    {
        if(volInfo->bootRecordOnImage->onImage)
        {
            srcFile = volInfo->imageForReading;
            readSeekSet(volInfo, volInfo->bootRecordOnImage->position, SEEK_SET);
            srcFileWasOpened = false;
        }
        else
        {
            srcFile = open(volInfo->bootRecordOnImage->pathAndName, O_RDONLY, 0);
            if(srcFile == -1)
                return BKERROR_OPEN_READ_FAILED;
            srcFileWasOpened = true;
        }
    }
    else

    {
        if(volInfo->bootRecordIsOnImage)
        {
            srcFile = volInfo->imageForReading;
            readSeekSet(volInfo, volInfo->bootRecordOffset, SEEK_SET);
            srcFileWasOpened = false;
        }
        else
        {
            srcFile = open(volInfo->bootRecordPathAndName, O_RDONLY, 0);
            if(srcFile == -1)
                return BKERROR_OPEN_READ_FAILED;
            srcFileWasOpened = true;
        }
    }


    destFile = open(destPathAndName, O_WRONLY | O_CREAT | O_TRUNC,
                    destFilePerms);
    if(destFile == -1)
    {
        if(srcFileWasOpened)
            bkClose(srcFile);
        return BKERROR_OPEN_WRITE_FAILED;
    }

    rc = copyByteBlock(volInfo, srcFile, destFile, volInfo->bootRecordSize);

    bkClose(destFile);
    if(srcFileWasOpened)
        bkClose(srcFile);

    if(rc <= 0)
        return rc;

    return 1;
}
