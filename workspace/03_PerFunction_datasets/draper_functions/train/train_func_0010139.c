bamMergeChunks(AjPBamIndex idx)
{
#if defined(BAM_TRUE_OFFSET) || defined(BAM_VIRTUAL_OFFSET16)
    AjPTable bindex = NULL;
    bam_binlist_t* p = NULL;
    bam_binlist_t** bins = NULL;
    ajint** binids = NULL;
    int i, m;
    ajulong n;
    ajuint l;
    ajulong k =0UL;

    for (i = 0; i < idx->n; ++i)
    {
	bindex = idx->bindex[i];

	n = ajTableToarrayKeysValues(bindex, (void***)&binids, (void***)&bins);

	for (k = 0; k<n; ++k)
	{

	    if(*binids[k] == BAM_MAX_BIN)
		continue;

	    p = bins[k];
	    m = 0;

	    for (l = 1; l < p->n; ++l)
	    {

#ifdef BAM_TRUE_OFFSET
		if (p->list[m].v + BAM_MIN_CHUNK_GAP > p->list[l].u)
		    p->list[m].v = p->list[l].v;
#else
		if (p->list[m].v>>16 == p->list[l].u>>16)
		    p->list[m].v = p->list[l].v;
#endif

		else
		    p->list[++m] = p->list[l];
	    }

	    p->n = m + 1;

	}
    }

    AJFREE(bins);
    AJFREE(binids);

#endif
}
