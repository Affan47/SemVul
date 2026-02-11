vcf_hdr_write(htsFile *fp, const bcf_hdr_t *h)
{
    int l = h->l_text;
    while (l && h->text[l-1] == 0) --l;
    int ret;
    if ( fp->is_compressed==1 )
        ret = bgzf_write(fp->fp.bgzf, h->text, l);
    else
        ret = hwrite(fp->fp.hfile, h->text, l);
    return ret<0 ? -1 : 0;
}
