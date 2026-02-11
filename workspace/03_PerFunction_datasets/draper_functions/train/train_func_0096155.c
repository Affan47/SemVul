opal_datatype_destroy( opal_datatype_t** dt )
{
    opal_datatype_t* pData = *dt;

    if( (pData->flags & OPAL_DATATYPE_FLAG_PREDEFINED) &&
        (pData->super.obj_reference_count <= 1) )
        return OPAL_ERROR;

    OBJ_RELEASE( pData );
    *dt = NULL;
    return OPAL_SUCCESS;
}
