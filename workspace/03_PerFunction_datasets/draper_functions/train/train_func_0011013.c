strformat_symbols_destroy(strformat_symbs_t* sbs)
{
    size_t i;
    if(!sbs)
        return;

    for(i = 0; i < strlen(sbs->symbols); ++i)
        free(sbs->contents[i]);
    free(sbs->contents);
    free(sbs->symbols);
    free(sbs);
}
