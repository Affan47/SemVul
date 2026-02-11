ompi_datatype_destroy( ompi_datatype_t** type)
{
    ompi_datatype_t* pData = *type;

    if( ompi_datatype_is_predefined(pData) && (pData->super.super.obj_reference_count <= 1) )
        return OMPI_ERROR;

    OBJ_RELEASE(pData);
    *type = NULL;
    return OMPI_SUCCESS;
}
