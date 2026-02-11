H5FL_blk_malloc(H5FL_blk_head_t *head, size_t size H5FL_TRACK_PARAMS)
{
    H5FL_blk_node_t *free_list;
    H5FL_blk_list_t *temp;
    void *ret_value;

    FUNC_ENTER_NOAPI(H5FL_blk_malloc, NULL)


    HDassert(head);
    HDassert(size);


    if(!head->init)
        if(H5FL_blk_init(head)<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTINIT, NULL, "can't initialize 'block' list")


    if((free_list=H5FL_blk_find_list(&(head->head),size))!=NULL && free_list->list!=NULL) {

        temp=free_list->list;
        free_list->list=free_list->list->next;


        head->onlist--;
        head->list_mem-=size;


        H5FL_blk_gc_head.mem_freed-=size;

    }

    else {

        if(NULL == (temp = (H5FL_blk_list_t *)H5FL_malloc(sizeof(H5FL_blk_list_t) + H5FL_TRACK_SIZE + size)))
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed for chunk")


        head->allocated++;
    }


    temp->size=size;


    ret_value=((char *)temp)+sizeof(H5FL_blk_list_t);

#ifdef H5FL_TRACK

    ((H5FL_track_t *)ret_value)->stack = H5MM_calloc(sizeof(H5CS_t));
    H5CS_copy_stack(((H5FL_track_t *)ret_value)->stack);
    ((H5FL_track_t *)ret_value)->file = H5MM_strdup(call_file);
    ((H5FL_track_t *)ret_value)->func = H5MM_strdup(call_func);
    ((H5FL_track_t *)ret_value)->line = call_line;


    ((H5FL_track_t *)ret_value)->prev = NULL;
    ((H5FL_track_t *)ret_value)->next = H5FL_out_head_g;
    if(H5FL_out_head_g)
        H5FL_out_head_g->prev = (H5FL_track_t *)ret_value;
    H5FL_out_head_g = (H5FL_track_t *)ret_value;


    ret_value = ((unsigned char *)ret_value) + sizeof(H5FL_track_t);
#endif

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
