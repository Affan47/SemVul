H5FL_fac_free(H5FL_fac_head_t *head, void *obj)
{
    void *ret_value=NULL;


    FUNC_ENTER_NOAPI_NOINIT


    HDassert(head);
    HDassert(obj);

#ifdef H5FL_TRACK
    {
        H5FL_track_t *trk = obj = ((unsigned char *)obj) - sizeof(H5FL_track_t);


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

#ifdef H5FL_DEBUG
    HDmemset(obj,255,head->size);
#endif


    HDassert(head->init);


    ((H5FL_fac_node_t *)obj)->next=head->list;


    head->list=(H5FL_fac_node_t *)obj;


    head->onlist++;


    H5FL_fac_gc_head.mem_freed+=head->size;


    if(head->onlist * head->size > H5FL_fac_lst_mem_lim)
        if(H5FL_fac_gc_list(head)<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGC, NULL, "garbage collection failed during free")


    if(H5FL_fac_gc_head.mem_freed > H5FL_fac_glb_mem_lim)
        if(H5FL_fac_gc()<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGC, NULL, "garbage collection failed during free")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
