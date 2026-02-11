kmclipm_vector_create(cpl_vector *data)
{
    kmclipm_vector *kv      = NULL;
    int             i       = 0,
                    n       = 0;
    double          *pdata  = NULL,
                    *pmask  = NULL;

    KMCLIPM_TRY
    {
        KMCLIPM_TRY_CHECK_AUTOMSG(data != NULL,
                                  CPL_ERROR_NULL_INPUT);

        KMCLIPM_TRY_EXIT_IFN(
            kv = (kmclipm_vector*)cpl_malloc(sizeof(kmclipm_vector)));

        kv->data = data;

        n = cpl_vector_get_size(data);
        KMCLIPM_TRY_EXIT_IFN(
            kv->mask = cpl_vector_new(n));

        KMCLIPM_TRY_EXIT_IFN(CPL_ERROR_NONE ==
            cpl_vector_fill(kv->mask, 1));

        KMCLIPM_TRY_EXIT_IFN(
            pdata = cpl_vector_get_data(kv->data));
        KMCLIPM_TRY_EXIT_IFN(
            pmask = cpl_vector_get_data(kv->mask));
        for (i = 0; i < n; i++)
        {
            if (kmclipm_is_nan_or_inf(pdata[i])) {

                pmask[i] = 0.;
            }
        }
    }
    KMCLIPM_CATCH
    {
        if (kv != NULL) {
            cpl_vector_delete(kv->data); kv->data = NULL;
            cpl_vector_delete(kv->mask); kv->mask = NULL;
        }
        cpl_free(kv); kv = NULL;
    }

    return kv;
}
