bcf_hdr_read(htsFile *hfp)
{
	if (!hfp->is_bin)
        return vcf_hdr_read(hfp);

    BGZF *fp = hfp->fp.bgzf;
	uint8_t magic[5];
	bcf_hdr_t *h;
	h = bcf_hdr_init("r");
	if ( bgzf_read(fp, magic, 5)<0 )
    {
        fprintf(stderr,"[%s:%d %s] Failed to read the header (reading BCF in text mode?)\n", __FILE__,__LINE__,__FUNCTION__);
        return NULL;
    }
	if (strncmp((char*)magic, "BCF\2\2", 5) != 0)
    {
        if (!strncmp((char*)magic, "BCF", 3))
            fprintf(stderr,"[%s:%d %s] invalid BCF2 magic string: only BCFv2.2 is supported.\n", __FILE__,__LINE__,__FUNCTION__);
		else if (hts_verbose >= 2)
			fprintf(stderr, "[E::%s] invalid BCF2 magic string\n", __func__);
		bcf_hdr_destroy(h);
		return 0;
	}
	bgzf_read(fp, &h->l_text, 4);
	h->text = (char*)malloc(h->l_text);
	bgzf_read(fp, h->text, h->l_text);
	bcf_hdr_parse(h);
	return h;
}
