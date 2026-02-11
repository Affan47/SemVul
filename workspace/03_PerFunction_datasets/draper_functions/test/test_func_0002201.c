rfio_HsmIf_chdir(const char *path) {
    int rc = -1;

#if defined(CNS_ROOT)
    if ( rfio_HsmIf_IsCnsFile(path) ) {
        if ( (rc = Cns_chdir(path)) == 0)
             rfio_HsmIf_SetCwdType(RFIO_HSM_CNS);
    }
#endif
    return(rc);
}
