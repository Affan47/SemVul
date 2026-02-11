bcf_sr_regions_destroy(bcf_sr_regions_t *reg)
{
    int i;
    free(reg->regs);
    free(reg->fname);
    if ( reg->itr ) tbx_itr_destroy(reg->itr);
    if ( reg->tbx ) tbx_destroy(reg->tbx);
    if ( reg->file ) hts_close(reg->file);
    if ( reg->als ) free(reg->als);
    free(reg->line.s);
    if (reg->regs)
        for (i=0; i<reg->nseqs; i++) free(reg->snames[i]);
    free(reg->snames);
    free(reg);
}
