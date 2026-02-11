_cmsChain2Lab(cmsContext            ContextID,
                            cmsUInt32Number        nProfiles,
                            cmsUInt32Number        InputFormat,
                            cmsUInt32Number        OutputFormat,
                            const cmsUInt32Number  Intents[],
                            const cmsHPROFILE      hProfiles[],
                            const cmsBool          BPC[],
                            const cmsFloat64Number AdaptationStates[],
                            cmsUInt32Number        dwFlags)
{
    cmsHTRANSFORM xform;
    cmsHPROFILE   hLab;
    cmsHPROFILE   ProfileList[256];
    cmsBool       BPCList[256];
    cmsFloat64Number AdaptationList[256];
    cmsUInt32Number IntentList[256];
    cmsUInt32Number i;


    if (nProfiles > 254) return NULL;


    hLab = cmsCreateLab4ProfileTHR(ContextID, NULL);
    if (hLab == NULL) return NULL;


    for (i=0; i < nProfiles; i++) {

        ProfileList[i]    = hProfiles[i];
        BPCList[i]        = BPC[i];
        AdaptationList[i] = AdaptationStates[i];
        IntentList[i]     = Intents[i];
    }


    ProfileList[nProfiles]    = hLab;
    BPCList[nProfiles]        = 0;
    AdaptationList[nProfiles] = 1.0;
    IntentList[nProfiles]     = INTENT_RELATIVE_COLORIMETRIC;


    xform = cmsCreateExtendedTransform(ContextID, nProfiles + 1, ProfileList,
                                       BPCList,
                                       IntentList,
                                       AdaptationList,
                                       NULL, 0,
                                       InputFormat,
                                       OutputFormat,
                                       dwFlags);

    cmsCloseProfile(hLab);

    return xform;
}
