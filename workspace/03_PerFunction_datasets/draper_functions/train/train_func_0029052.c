cmsGetTagSignature(cmsHPROFILE hProfile, cmsUInt32Number n)
{
    _cmsICCPROFILE* Icc = (_cmsICCPROFILE*) hProfile;

    if (n > Icc->TagCount) return (cmsTagSignature) 0;
    if (n >= MAX_TABLE_TAG) return (cmsTagSignature) 0;

    return Icc ->TagNames[n];
}
