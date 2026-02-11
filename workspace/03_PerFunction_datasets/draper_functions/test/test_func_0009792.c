kmclipm_vector_extract(const kmclipm_vector *kv,
                                       int istart,
                                       int istop)
{
    kmclipm_vector  *kv_out = NULL;

    KMCLIPM_TRY
    {
        KMCLIPM_TRY_CHECK_AUTOMSG(kv != NULL,
                                  CPL_ERROR_NULL_INPUT);

        KMCLIPM_TRY_CHECK_AUTOMSG(istop > istart,
                                  CPL_ERROR_ILLEGAL_INPUT);

        KMCLIPM_TRY_EXIT_IFN(
            kv_out = (kmclipm_vector*)cpl_malloc(sizeof(kmclipm_vector)));

        KMCLIPM_TRY_EXIT_IFN(
            kv_out->data = cpl_vector_extract(kv->data, istart, istop, 1));

        KMCLIPM_TRY_EXIT_IFN(
            kv_out->mask = cpl_vector_extract(kv->mask, istart, istop, 1));
    }
    KMCLIPM_CATCH
    {
        if (kv_out != NULL) {
            cpl_vector_delete(kv_out->data); kv_out->data = NULL;
            cpl_vector_delete(kv_out->mask); kv_out->mask = NULL;
        }
        cpl_free(kv_out); kv_out = NULL;
    }

    return kv_out;
}
