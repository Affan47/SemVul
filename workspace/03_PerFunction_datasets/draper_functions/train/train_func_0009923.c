kmclipm_vector_count_rejected(const kmclipm_vector *kv)
{
    int     cnt     = 0,
            i       = 0;
    double  *pmask = NULL;

    KMCLIPM_TRY
    {
        KMCLIPM_TRY_CHECK_AUTOMSG(kv != NULL,
                                  CPL_ERROR_NULL_INPUT);

        KMCLIPM_TRY_EXIT_IFN(
            pmask = cpl_vector_get_data(kv->mask));
        for (i = 0; i < cpl_vector_get_size(kv->mask); i++) {
            if (pmask[i] == 0) {
                cnt++;
            }
        }
    }
    KMCLIPM_CATCH
    {
        cnt = -1;
    }

    return cnt;
}
