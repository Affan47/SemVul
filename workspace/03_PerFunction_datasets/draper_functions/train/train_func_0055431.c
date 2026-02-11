zc_crk_bforce_set_vdata(struct zc_crk_bforce *crk, const struct zc_validation_data *vdata, size_t nmemb)
{
    if (!vdata)
        return -EINVAL;
    if (nmemb == 0)
        return -EINVAL;
    crk->vdata = vdata;
    crk->vdata_size = nmemb;
    return 0;
}
