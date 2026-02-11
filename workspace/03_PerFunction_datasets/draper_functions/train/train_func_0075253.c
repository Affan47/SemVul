Scan( const char *FileName )
{
#ifdef CL_INIT_DEFAULT
    int ret = cl_scanfile(FileName, &virname, NULL, engine, scanopts);
#else
    int ret = cl_scanfile(FileName, &virname, NULL, engine, &limits, scanopts);
#endif


    if ( ret == CL_CLEAN )
    {
        ScannerAnswer = "0Clean";
        return ScannerAnswer;
    }


    if ( ret == CL_VIRUS )
    {

        if ( (strstr(virname, "Oversized.") != NULL) && (Params::GetConfigBool("CLAMBLOCKMAX") == false) )
        {
            ScannerAnswer = "0Clean";
            return ScannerAnswer;
        }

        ScannerAnswer = "1";
        ScannerAnswer += virname;
        return ScannerAnswer;
    }


    ScannerAnswer = "2";
    ScannerAnswer += cl_strerror(ret);
    return ScannerAnswer;
}
