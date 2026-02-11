make_no_loopdat_set(List *baa_list, LoopDat *lpdat_head)
{
    List *li;
    List *nlp_list = NULL;
    BlockAlignArray *baa;
    for(li = baa_list; li != NULL; li = li->next){
	baa = (BlockAlignArray *)li->data;
	if(is_block_no_lpdat(baa, lpdat_head))
	    nlp_list = list_append(nlp_list ,li->data);
    }
    return nlp_list;
}
