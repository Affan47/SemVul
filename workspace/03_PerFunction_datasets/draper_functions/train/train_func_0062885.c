xmlSecGnuTLSDestroyMpis(gcry_mpi_t * mpis, xmlSecSize num) {
    xmlSecSize ii;

    xmlSecAssert(mpis != NULL);
    for(ii = 0; ii < num; ++ii) {
        gcry_mpi_release(mpis[ii]);
    }
}
