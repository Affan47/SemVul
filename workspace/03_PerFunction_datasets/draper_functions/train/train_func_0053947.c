readPosixFileMode(VolInfo* volInfo, unsigned* posixFileMode, int lenSU)
{
    bk_off_t origPos;
    unsigned char* suFields;
    int rc;
    bool foundPosix;
    bool foundCE;
    int count;
    unsigned logicalBlockOfCE;
    unsigned offsetInLogicalBlockOfCE;
    unsigned lengthOfCE;

    suFields = malloc(lenSU);
    if(suFields == NULL)
        return BKERROR_OUT_OF_MEMORY;

    origPos = readSeekTell(volInfo);

    rc = readRead(volInfo, suFields, lenSU);

    if(rc != lenSU)
        return BKERROR_READ_GENERIC;
    count = 0;
    foundPosix = false;
    foundCE = false;
    while(count < lenSU && !foundPosix)
    {
        if(suFields[count] == 0)


            break;

        if(suFields[count] == 'P' && suFields[count + 1] == 'X')
        {

            read733FromCharArray(suFields + count + 4, posixFileMode);


            foundPosix = true;
        }
        else if(suFields[count] == 'C' && suFields[count + 1] == 'E')
        {
            foundCE = true;
            read733FromCharArray(suFields + count + 4, &logicalBlockOfCE);
            read733FromCharArray(suFields + count + 12, &offsetInLogicalBlockOfCE);
            read733FromCharArray(suFields + count + 20, &lengthOfCE);
        }


        count += suFields[count + 2];
    }

    free(suFields);
    readSeekSet(volInfo, origPos, SEEK_SET);

    if(!foundPosix)
    {
        if(!foundCE)
            return BKERROR_NO_POSIX_PRESENT;
        else
        {
            readSeekSet(volInfo, logicalBlockOfCE * NBYTES_LOGICAL_BLOCK +
                        offsetInLogicalBlockOfCE, SEEK_SET);
            rc = readPosixFileMode(volInfo, posixFileMode, lengthOfCE);

            readSeekSet(volInfo, origPos, SEEK_SET);

            return rc;
        }
    }

    return 1;
}
