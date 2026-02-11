ompi_osc_base_get_primitive_type_info(ompi_datatype_t *datatype,
                                      ompi_datatype_t **prim_datatype,
                                      uint32_t *prim_count)
{
    ompi_datatype_t *primitive_datatype = NULL;
    size_t datatype_size, primitive_size, primitive_count;

    primitive_datatype = ompi_datatype_get_single_predefined_type_from_args(datatype);
    if( NULL == primitive_datatype ) {
        *prim_count = 0;
        return OMPI_SUCCESS;
    }
    ompi_datatype_type_size( datatype, &datatype_size );
    ompi_datatype_type_size( primitive_datatype, &primitive_size );
    primitive_count = datatype_size / primitive_size;
#if OPAL_ENABLE_DEBUG
    assert( 0 == (datatype_size % primitive_size) );
#endif


    *prim_datatype = primitive_datatype;
    *prim_count = (uint32_t)primitive_count;

    return OMPI_SUCCESS;
}
