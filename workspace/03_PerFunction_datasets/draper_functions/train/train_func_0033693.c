opal_datatype_init( void )
{
    const opal_datatype_t* datatype;
    int32_t i;

    for( i = OPAL_DATATYPE_FIRST_TYPE; i < OPAL_DATATYPE_MAX_PREDEFINED; i++ ) {
        datatype = opal_datatype_basicDatatypes[i];


        datatype->desc.desc[0].elem.common.flags = OPAL_DATATYPE_FLAG_PREDEFINED |
                                                   OPAL_DATATYPE_FLAG_DATA |
                                                   OPAL_DATATYPE_FLAG_CONTIGUOUS |
                                                   OPAL_DATATYPE_FLAG_NO_GAPS;
        datatype->desc.desc[0].elem.common.type  = i;

        datatype->desc.desc[0].elem.count        = 1;
        datatype->desc.desc[0].elem.disp         = 0;
        datatype->desc.desc[0].elem.extent       = datatype->size;

        datatype->desc.desc[1].end_loop.common.flags    = 0;
        datatype->desc.desc[1].end_loop.common.type     = OPAL_DATATYPE_END_LOOP;
        datatype->desc.desc[1].end_loop.items           = 1;
        datatype->desc.desc[1].end_loop.first_elem_disp = datatype->desc.desc[0].elem.disp;
        datatype->desc.desc[1].end_loop.size            = datatype->size;
    }

    return OPAL_SUCCESS;
}
