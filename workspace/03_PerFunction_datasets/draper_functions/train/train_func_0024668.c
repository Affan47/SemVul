JstfLangFree(struct jstf_lang *jl) {
    struct jstf_lang *next;
    int i;

    while ( jl!=NULL ) {
	next = jl->next;
	for ( i=0; i<jl->cnt; ++i ) {
	    struct jstf_prio *jp = &jl->prios[i];
	    free(jp->enableShrink);
	    free(jp->disableShrink);
	    free(jp->maxShrink);
	    free(jp->enableExtend);
	    free(jp->disableExtend);
	    free(jp->maxExtend);
	}
	free(jl->prios);
	chunkfree(jl,sizeof(*jl));
	jl = next;
    }
}
