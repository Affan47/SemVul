rfio_HsmIf_IsHsmFile(const char *path) {
    int rc = 0;

    if ( (rc = rfio_HsmIf_IsCnsFile(path)) == 1 ) return(rc);
    return(rc);
}
