sam_hdr_free(SAM_hdr *hdr) {
    if (!hdr)
	return;

    if (--hdr->ref_count > 0)
	return;

    if (ks_str(&hdr->text))
	KS_FREE(&hdr->text);

    if (hdr->h)
	kh_destroy(sam_hdr, hdr->h);

    if (hdr->ref_hash)
	kh_destroy(m_s2i, hdr->ref_hash);

    if (hdr->ref) {
	int i;
	for (i = 0; i < hdr->nref; i++)
	    if (hdr->ref[i].name)
		free(hdr->ref[i].name);
	free(hdr->ref);
    }

    if (hdr->rg_hash)
	kh_destroy(m_s2i, hdr->rg_hash);

    if (hdr->rg) {
	int i;
	for (i = 0; i < hdr->nrg; i++)
	    if (hdr->rg[i].name)
		free(hdr->rg[i].name);
	free(hdr->rg);
    }

    if (hdr->pg_hash)
	kh_destroy(m_s2i, hdr->pg_hash);

    if (hdr->pg) {
	int i;
	for (i = 0; i < hdr->npg; i++)
	    if (hdr->pg[i].name)
		free(hdr->pg[i].name);
	free(hdr->pg);
    }

    if (hdr->pg_end)
	free(hdr->pg_end);

    if (hdr->type_pool)
	pool_destroy(hdr->type_pool);

    if (hdr->tag_pool)
	pool_destroy(hdr->tag_pool);

    if (hdr->str_pool)
	string_pool_destroy(hdr->str_pool);

    free(hdr);
}
