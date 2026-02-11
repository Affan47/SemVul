opal_convertor_create_stack_with_pos_contig( opal_convertor_t* pConvertor,
                                                               size_t starting_point, const size_t* sizes )
{
    dt_stack_t* pStack;
    const opal_datatype_t* pData = pConvertor->pDesc;
    dt_elem_desc_t* pElems;
    uint32_t count;
    OPAL_PTRDIFF_TYPE extent;

    pStack = pConvertor->pStack;


    pElems = pConvertor->use_desc->desc;

    count = (uint32_t)(starting_point / pData->size);
    extent = pData->ub - pData->lb;

    pStack[0].type     = OPAL_DATATYPE_LOOP;
    pStack[0].count    = pConvertor->count - count;
    pStack[0].index    = -1;
    pStack[0].disp     = count * extent;


    count = (uint32_t)(starting_point - count * pData->size);


    if( OPAL_LIKELY(0 == count) ) {
        pStack[1].type     = pElems->elem.common.type;
        pStack[1].count    = pElems->elem.count;
        pStack[1].disp     = pElems->elem.disp;
    } else {
        pStack[1].type  = OPAL_DATATYPE_UINT1;
        pStack[1].count = pData->size - count;
        pStack[1].disp  = pData->true_lb + count;
    }
    pStack[1].index    = 0;

    pConvertor->bConverted = starting_point;
    pConvertor->stack_pos = 1;
    assert( 0 == pConvertor->partial_length );
    return OPAL_SUCCESS;
}
