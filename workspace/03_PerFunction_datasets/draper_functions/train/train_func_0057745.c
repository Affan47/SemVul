camAllocateKeypointsMatches(CamKeypointsMatches *matches, int nbpairs)
{
    matches->pairs = (CamKeypointsMatch*)malloc(nbpairs * sizeof(CamKeypointsMatch));
    matches->nbMatches = 0;
    matches->nbOutliers = 0;
    if (matches->pairs == NULL) return 0;
    matches->allocated = nbpairs;
    return 1;
}
