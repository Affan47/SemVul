opal_datatype_get_element_count( const opal_datatype_t* datatype, size_t iSize )
{
    dt_stack_t* pStack;
    uint32_t pos_desc;
    ssize_t nbElems = 0, stack_pos = 0;
    size_t local_size;
    dt_elem_desc_t* pElems;


    assert( (uint32_t)iSize <= datatype->size );
    DUMP( "dt_count_elements( %p, %d )\n", (void*)datatype, iSize );
    pStack = (dt_stack_t*)alloca( sizeof(dt_stack_t) * (datatype->btypes[OPAL_DATATYPE_LOOP] + 2) );
    pStack->count    = 1;
    pStack->index    = -1;
    pStack->disp     = 0;
    pElems           = datatype->desc.desc;
    pos_desc         = 0;

    while( 1 ) {
        if( OPAL_DATATYPE_END_LOOP == pElems[pos_desc].elem.common.type ) {
            if( --(pStack->count) == 0 ) {
                stack_pos--; pStack--;
                if( stack_pos == -1 ) return nbElems;
            }
            pos_desc = pStack->index + 1;
            continue;
        }
        if( OPAL_DATATYPE_LOOP == pElems[pos_desc].elem.common.type ) {
            ddt_loop_desc_t* loop = &(pElems[pos_desc].loop);
            do {
                PUSH_STACK( pStack, stack_pos, pos_desc, OPAL_DATATYPE_LOOP, loop->loops, 0 );
                pos_desc++;
            } while( OPAL_DATATYPE_LOOP == pElems[pos_desc].elem.common.type );
            DDT_DUMP_STACK( pStack, stack_pos, pElems, "advance loops" );
        }
        while( pElems[pos_desc].elem.common.flags & OPAL_DATATYPE_FLAG_DATA ) {

            const opal_datatype_t* basic_type = BASIC_DDT_FROM_ELEM(pElems[pos_desc]);
            local_size = pElems[pos_desc].elem.count * basic_type->size;
            if( local_size >= iSize ) {
                local_size = iSize / basic_type->size;
                nbElems += (int32_t)local_size;
                iSize -= local_size * basic_type->size;
                return (iSize == 0 ? nbElems : -1);
            }
            nbElems += pElems[pos_desc].elem.count;
            iSize -= local_size;
            pos_desc++;
        }
    }
}
