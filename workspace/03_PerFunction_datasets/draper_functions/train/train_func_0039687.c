opal_datatype_set_element_count( const opal_datatype_t* datatype, size_t count, size_t* length )
{
    dt_stack_t* pStack;
    size_t pos_desc;
    int32_t stack_pos = 0;
    size_t local_length = 0;
    dt_elem_desc_t* pElems;


    for( pos_desc = 4; pos_desc < OPAL_DATATYPE_MAX_PREDEFINED; pos_desc++ ) {
        local_length += datatype->btypes[pos_desc];
    }
    pos_desc = count / local_length;
    count = count % local_length;
    *length = datatype->size * pos_desc;
    if( 0 == count ) {
        return 0;
    }

    DUMP( "dt_set_element_count( %p, %d )\n", (void*)datatype, count );
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
                if( stack_pos == -1 ) return 0;
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
            local_length = pElems[pos_desc].elem.count;
            if( local_length >= count ) {
                *length += count * basic_type->size;
                return 0;
            }
            *length += local_length * basic_type->size;
            count -= local_length;
            pos_desc++;
        }
    }
}
