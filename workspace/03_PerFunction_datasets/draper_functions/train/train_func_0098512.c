nchashremove(NChashmap* hm, nchashid hash)
{
    int i,offset,len;
    NClist* seq;
    ncelem* list;

    offset = (hash % hm->alloc);
    seq = hm->table[offset];
    if(seq == NULL) return TRUE;
    len = nclistlength(seq);
    list = nclistcontents(seq);
    for(i=0;i<len;i+=2,list+=2) {
	if(*list == hash) {
	    nclistremove(seq,i+1);
	    nclistremove(seq,i);
	    hm->size--;
	    if(nclistlength(seq) == 0) {nclistfree(seq); hm->table[offset] = NULL;}
	    return TRUE;
	}
    }
    return FALSE;
}
