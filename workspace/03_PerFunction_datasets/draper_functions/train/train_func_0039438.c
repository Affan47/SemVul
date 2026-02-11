bcf_sr_regions_init(const char *regions)
{
    bcf_sr_regions_t *reg = _regions_init_string(regions);
    if ( reg ) return reg;

    reg = (bcf_sr_regions_t *) calloc(1, sizeof(bcf_sr_regions_t));
    reg->ireg = -1;

    reg->file = hts_open(regions, "rb");
    if ( !reg->file )
    {
        fprintf(stderr,"[%s:%d %s] Could not open file: %s\n", __FILE__,__LINE__,__FUNCTION__,regions);
        free(reg);
        return NULL;
    }

    reg->tbx = tbx_index_load(regions);
    if ( !reg->tbx )
    {
        fprintf(stderr,"[%s:%d %s] Could not load tabix index: %s\n", __FILE__,__LINE__,__FUNCTION__,regions);
        free(reg);
        return NULL;
    }
    reg->snames = (char**) tbx_seqnames(reg->tbx, &reg->nseqs);
    reg->fname  = strdup(regions);
    reg->is_bin = 1;
    return reg;
}
