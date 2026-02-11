bk_set_permissions(VolInfo* volInfo, const char* pathAndName,
                       mode_t permissions)
{
    int rc;
    NewPath srcPath;
    BkFileBase* base;
    bool itemFound;

    rc = makeNewPathFromString(pathAndName, &srcPath);
    if(rc <= 0)
    {
        freePathContents(&srcPath);
        return rc;
    }

    itemFound = findBaseByNewPath(&srcPath, &(volInfo->dirTree), &base);

    freePathContents(&srcPath);

    if(!itemFound)
        return BKERROR_ITEM_NOT_FOUND_ON_IMAGE;


    base->posixFileMode &= ~0777;


    base->posixFileMode |= permissions & 0777;

    return 1;
}
