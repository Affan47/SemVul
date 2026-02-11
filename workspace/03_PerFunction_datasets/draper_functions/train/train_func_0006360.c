destruct_template_info(Ya_template_info *tinfo, const int amax)
{
    int i;

    for (i = 0; i < amax + 1; i++) {
        if (tinfo->dim_size[i] != NULL) {
            free(tinfo->dim_size[i]);
        }
    }
    free(tinfo->dim_size);
    free(tinfo->aes);
}
