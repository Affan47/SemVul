aff_toc_update(AFFILE *af,const char *segname,uint64_t offset,uint64_t datalen)
{
    for(int i=0;i<af->toc_count;i++){
	if(af->toc[i].name==0 || strcmp(af->toc[i].name,segname)==0){
	    if(af->toc[i].name==0){
		af->toc[i].name = strdup(segname);
	    }
	    af->toc[i].offset  = offset;
	    af->toc[i].segment_len = aff_segment_overhead(segname)+datalen;
	    return;
	}
    }
    aff_toc_append(af,segname,offset,datalen);
}
