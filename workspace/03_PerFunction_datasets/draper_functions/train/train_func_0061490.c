H5HL_fl_deserialize(H5HL_t *heap)
{
    H5HL_free_t *fl = NULL, *tail = NULL;
    hsize_t free_block;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(heap);
    HDassert(!heap->freelist);


    free_block = heap->free_block;
    while(H5HL_FREE_NULL != free_block) {
        const uint8_t *p;


        if(free_block >= heap->dblk_size)
            HGOTO_ERROR(H5E_HEAP, H5E_BADRANGE, FAIL, "bad heap free list")


        if(NULL == (fl = H5FL_MALLOC(H5HL_free_t)))
            HGOTO_ERROR(H5E_HEAP, H5E_CANTALLOC, FAIL, "memory allocation failed")
        fl->offset = (size_t)free_block;
        fl->prev = tail;
        fl->next = NULL;


        p = heap->dblk_image + free_block;
        H5F_DECODE_LENGTH_LEN(p, free_block, heap->sizeof_size);
        if(free_block == 0)
            HGOTO_ERROR(H5E_HEAP, H5E_BADVALUE, FAIL, "free block size is zero?")


        H5F_DECODE_LENGTH_LEN(p, fl->size, heap->sizeof_size);
        if((fl->offset + fl->size) > heap->dblk_size)
            HGOTO_ERROR(H5E_HEAP, H5E_BADRANGE, FAIL, "bad heap free list")


        if(tail)
            tail->next = fl;
        else
            heap->freelist = fl;
        tail = fl;
        fl = NULL;
    }

done:
    if(ret_value < 0)
        if(fl)
            fl = H5FL_FREE(H5HL_free_t, fl);

    FUNC_LEAVE_NOAPI(ret_value)
}
