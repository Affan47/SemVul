search_heap_in_loop(Block *loop, Block *first_block,
		    Define_table *define_heap_list,
		    Define_table *modified_heap_list)
{
    Block *bpt;
    Statement *spt;
    Boolean find_heap = FALSE;

    for( bpt = first_block; bpt; bpt = bpt->next){
        if (bpt->inner != NULL){
            if( search_heap_in_loop(loop, bpt->inner, define_heap_list, modified_heap_list) )
                find_heap = TRUE;

        }else {
            for(spt = bpt->pre_head->stm_head; spt; spt = spt->next){
                if( set_define_list_for_heap(loop, spt, define_heap_list, modified_heap_list) )
                    find_heap = TRUE;
            }
        }
    }

    return find_heap;
}
