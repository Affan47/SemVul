H5HP_insert(H5HP_t *heap, int val, void *obj)
{
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(H5HP_insert,FAIL);


    assert(heap);
    assert(obj);


    assert(heap->nobjs<heap->nalloc);
    assert(heap->heap);
    assert((heap->type==H5HP_MAX_HEAP && heap->heap[0].val==INT_MAX) ||
        (heap->type==H5HP_MIN_HEAP && heap->heap[0].val==INT_MIN));
    assert(heap->heap[0].obj==NULL);


    heap->nobjs++;


    if(heap->nobjs>=heap->nalloc) {
        size_t n = MAX(H5HP_START_SIZE, 2*(heap->nalloc-1)) + 1;
        H5HP_ent_t *new_heap = H5FL_SEQ_REALLOC(H5HP_ent_t,heap->heap, n);

        if (!new_heap)
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "unable to extend heap array");
        heap->heap = new_heap;
        heap->nalloc = n;
    }


    heap->heap[heap->nobjs].val = val;
    heap->heap[heap->nobjs].obj = (H5HP_info_t *)obj;
    heap->heap[heap->nobjs].obj->heap_loc = heap->nobjs;


    if(heap->type==H5HP_MAX_HEAP) {
        if(H5HP_swim_max(heap,heap->nobjs)<0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINSERT, FAIL, "unable to restore heap condition");
    }
    else {
        if(H5HP_swim_min(heap,heap->nobjs)<0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINSERT, FAIL, "unable to restore heap condition");
    }

done:


    assert(heap->nobjs<heap->nalloc);
    assert(heap->heap);
    assert((heap->type==H5HP_MAX_HEAP && heap->heap[0].val==INT_MAX) ||
        (heap->type==H5HP_MIN_HEAP && heap->heap[0].val==INT_MIN));
    assert(heap->heap[0].obj==NULL);

    FUNC_LEAVE_NOAPI(ret_value);
}
