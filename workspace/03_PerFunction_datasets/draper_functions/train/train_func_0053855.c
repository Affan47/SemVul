H5FL_blk_free(H5FL_blk_head_t *head, void *block)
{
    H5FL_blk_node_t *free_list;
    H5FL_blk_list_t *temp;
    size_t free_size;
    void *ret_value=NULL;


    FUNC_ENTER_NOAPI_NOINIT


    HDassert(head);
    HDassert(block);

#ifdef H5FL_TRACK
    {
        H5FL_track_t *trk = block = ((unsigned char *)block) - sizeof(H5FL_track_t);


        H5CS_close_stack(trk->stack);
        trk->stack = H5MM_xfree(trk->stack);
        trk->file = H5MM_xfree(trk->file);
        trk->func = H5MM_xfree(trk->func);


        if(trk == H5FL_out_head_g) {
            H5FL_out_head_g = H5FL_out_head_g->next;
            if(H5FL_out_head_g)
                H5FL_out_head_g->prev = NULL;
        }
        else {
            trk->prev->next = trk->next;
            if(trk->next)
                trk->next->prev = trk->prev;
        }
    }
#endif


    temp=(H5FL_blk_list_t *)((unsigned char *)block-sizeof(H5FL_blk_list_t));


    free_size=temp->size;

#ifdef H5FL_DEBUG
    HDmemset(temp,255,free_size + sizeof(H5FL_blk_list_t) + H5FL_TRACK_SIZE);
#endif


    if((free_list=H5FL_blk_find_list(&(head->head),free_size))==NULL) {

        free_list=H5FL_blk_create_list(&(head->head),free_size);
        HDassert(free_list);
    }


    if(free_list!=NULL) {
        temp->next=free_list->list;
        free_list->list=temp;
    }


    head->onlist++;
    head->list_mem+=free_size;


    H5FL_blk_gc_head.mem_freed+=free_size;


    if(head->list_mem>H5FL_blk_lst_mem_lim)
        if(H5FL_blk_gc_list(head)<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGC, NULL, "garbage collection failed during free")


    if(H5FL_blk_gc_head.mem_freed>H5FL_blk_glb_mem_lim)
        if(H5FL_blk_gc()<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGC, NULL, "garbage collection failed during free")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
