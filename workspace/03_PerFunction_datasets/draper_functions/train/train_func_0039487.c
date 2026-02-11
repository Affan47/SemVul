bk_estimate_iso_size(const VolInfo* volInfo, int filenameTypes)
{

    BkHardLink* currentLink;
    currentLink = volInfo->fileLocations;
    while(currentLink != NULL)
    {
        currentLink->alreadyCounted = false;

        currentLink = currentLink->next;
    }

    return estimateIsoSize(&(volInfo->dirTree), filenameTypes);
}
