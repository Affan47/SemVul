mca_base_pvar_mark_invalid (int index)
{
    mca_base_pvar_t *pvar;
    int ret;

    ret = mca_base_pvar_get_internal (index, &pvar, false);
    if (OPAL_SUCCESS != ret) {
        return ret;
    }

    pvar->flags |= MCA_BASE_PVAR_FLAG_INVALID;

    return OPAL_SUCCESS;
}
