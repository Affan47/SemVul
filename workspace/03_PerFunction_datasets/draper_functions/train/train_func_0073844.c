opal_convertor_prepare_for_recv( opal_convertor_t* convertor,
                                         const struct opal_datatype_t* datatype,
                                         int32_t count,
                                         const void* pUserBuf )
{


    convertor->flags |= CONVERTOR_RECV;
#if OPAL_CUDA_SUPPORT
    mca_cuda_convertor_init(convertor, pUserBuf);
#endif

    OPAL_CONVERTOR_PREPARE( convertor, datatype, count, pUserBuf );

    if( convertor->flags & CONVERTOR_WITH_CHECKSUM ) {
#if OPAL_ENABLE_HETEROGENEOUS_SUPPORT
        if( !(convertor->flags & CONVERTOR_HOMOGENEOUS) ) {
            convertor->fAdvance = opal_unpack_general_checksum;
        } else
#endif
        if( convertor->pDesc->flags & OPAL_DATATYPE_FLAG_CONTIGUOUS ) {
            convertor->fAdvance = opal_unpack_homogeneous_contig_checksum;
        } else {
            convertor->fAdvance = opal_generic_simple_unpack_checksum;
        }
    } else {
#if OPAL_ENABLE_HETEROGENEOUS_SUPPORT
        if( !(convertor->flags & CONVERTOR_HOMOGENEOUS) ) {
            convertor->fAdvance = opal_unpack_general;
        } else
#endif
        if( convertor->pDesc->flags & OPAL_DATATYPE_FLAG_CONTIGUOUS ) {
            convertor->fAdvance = opal_unpack_homogeneous_contig;
        } else {
            convertor->fAdvance = opal_generic_simple_unpack;
        }
    }
    return OPAL_SUCCESS;
}
