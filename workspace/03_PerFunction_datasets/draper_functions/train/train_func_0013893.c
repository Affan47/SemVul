camFPKdTreeCompare(const void *fp1x, const void *fp2x)
{
    CamKeypoint **fp1 = (CamKeypoint**)fp1x;
    CamKeypoint **fp2 = (CamKeypoint**)fp2x;
    if ((*fp1)->descriptor[(int)(*fp1)->internal] > (*fp2)->descriptor[(int)(*fp2)->internal]) return 1;
    if ((*fp1)->descriptor[(int)(*fp1)->internal] == (*fp2)->descriptor[(int)(*fp2)->internal]) return 0;
    return -1;
}
