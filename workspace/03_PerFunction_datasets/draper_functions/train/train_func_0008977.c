lrmd_copy_rsc_info(lrmd_rsc_info_t * rsc_info)
{
    lrmd_rsc_info_t *copy = NULL;

    copy = calloc(1, sizeof(lrmd_rsc_info_t));

    copy->id = strdup(rsc_info->id);
    copy->type = strdup(rsc_info->type);
    copy->class = strdup(rsc_info->class);
    if (rsc_info->provider) {
        copy->provider = strdup(rsc_info->provider);
    }

    return copy;
}
