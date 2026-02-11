cmsSaveProfileToMem(cmsHPROFILE hProfile, void *MemPtr, cmsUInt32Number* BytesNeeded)
{
    cmsBool rc;
    cmsIOHANDLER* io;
    cmsContext ContextID = cmsGetProfileContextID(hProfile);


    if (MemPtr == NULL) {

           *BytesNeeded =  cmsSaveProfileToIOhandler(hProfile, NULL);
            return TRUE;
    }


    io =  cmsOpenIOhandlerFromMem(ContextID, MemPtr, *BytesNeeded, "w");
    if (io == NULL) return FALSE;

    rc = (cmsSaveProfileToIOhandler(hProfile, io) != 0);
    rc &= cmsCloseIOhandler(io);

    return rc;
}
