caps_init (void)
{
    static int init = 0, noticed = 0;
    int i;
    HMODULE h;
    TCHAR *dllname = "CAPSImg.dll";

    if (init)
        return 1;

#if WINDOWS
    h = LoadLibrary (dllname);
    if (!h) {
        write_log("LoadLibrary (\"CAPSImg.dll\") failed\n");
        TCHAR tmp[MAX_DPATH];
        if (SUCCEEDED (SHGetFolderPath (NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, 0, tmp))) {
            _tcscat (tmp, "\\Software Preservation Society\\");
            _tcscat (tmp, dllname);
            h = LoadLibrary (tmp);
            if (!h) {
                if (noticed)
                    return 0;
                notify_user (NUMSG_NOCAPS);
                noticed = 1;
                return 0;
            }
        }
    }
#else
    h = load_caps_library();
    if (h == NULL) {
        if (noticed) {
            return 0;
        }
        notify_user (NUMSG_NOCAPS);
        noticed = 1;
        return 0;
    }
#endif
    if (GetProcAddress (h, "CAPSLockImageMemory") == 0 || GetProcAddress (h, "CAPSGetVersionInfo") == 0) {
        if (noticed)
            return 0;
        notify_user (NUMSG_OLDCAPS);
        noticed = 1;
        return 0;
    }
    pCAPSInit = (CAPSINIT)GetProcAddress (h, "CAPSInit");
    pCAPSAddImage = (CAPSADDIMAGE)GetProcAddress (h, "CAPSAddImage");
    pCAPSLockImageMemory = (CAPSLOCKIMAGEMEMORY)GetProcAddress (h, "CAPSLockImageMemory");
    pCAPSUnlockImage = (CAPSUNLOCKIMAGE)GetProcAddress (h, "CAPSUnlockImage");
    pCAPSLoadImage = (CAPSLOADIMAGE)GetProcAddress (h, "CAPSLoadImage");
    pCAPSGetImageInfo = (CAPSGETIMAGEINFO)GetProcAddress (h, "CAPSGetImageInfo");
    pCAPSLockTrack = (CAPSLOCKTRACK)GetProcAddress (h, "CAPSLockTrack");
    pCAPSUnlockTrack = (CAPSUNLOCKTRACK)GetProcAddress (h, "CAPSUnlockTrack");
    pCAPSUnlockAllTracks = (CAPSUNLOCKALLTRACKS)GetProcAddress (h, "CAPSUnlockAllTracks");
    pCAPSGetVersionInfo = (CAPSGETVERSIONINFO)GetProcAddress (h, "CAPSGetVersionInfo");
    init = 1;
    cvi.type = 1;
    pCAPSGetVersionInfo (&cvi, 0);
    write_log ("CAPS: library version %u.%u (flags=%08X)\n",
            cvi.release, cvi.revision, cvi.flag);
    oldlib = (cvi.flag & (DI_LOCK_TRKBIT | DI_LOCK_OVLBIT)) != (DI_LOCK_TRKBIT | DI_LOCK_OVLBIT);
    if (!oldlib)
        caps_flags |= DI_LOCK_TRKBIT | DI_LOCK_OVLBIT;
    canseed = (cvi.flag & DI_LOCK_SETWSEED) != 0;
    for (i = 0; i < 4; i++)
        caps_cont[i] = pCAPSAddImage ();
    return 1;
}
