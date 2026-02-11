SWsdid(int32 swathID, const char *fieldname, int32 *sdid)
{
    intn            status;
    int32           fid;
    int32           sdInterfaceID;
    int32           dum;
    int32           dims[H4_MAX_VAR_DIMS];

    status = SWchkswid(swathID, "SWsdid", &fid, &sdInterfaceID, &dum);
    if (status != -1)
    {
        status = SWSDfldsrch(swathID, sdInterfaceID, fieldname,
                             sdid, &dum, &dum, &dum, dims, &dum);
    }

    return (status);
}
