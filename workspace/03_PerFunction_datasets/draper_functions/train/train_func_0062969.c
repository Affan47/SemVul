modperl_cleanup_pnotes(void *data) {
    HV **pnotes = data;

    if (*pnotes) {
#ifdef USE_ITHREADS
        modperl_cleanup_pnotes_data_t *cleanup_data = data;
        dTHXa(cleanup_data->perl);
        pnotes = cleanup_data->pnotes;
#else
        pnotes = data;
#endif
        SvREFCNT_dec(*pnotes);
        *pnotes = (HV *)NULL;
    }

    return APR_SUCCESS;
}
