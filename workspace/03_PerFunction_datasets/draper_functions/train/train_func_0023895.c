nchashlookup(NChashmap* hm, nchashid hash, ncelem* valuep)
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
	if(*list == hash) {if(valuep) {*valuep = list[1]; return TRUE;}}
    }
    return FALSE;
}
