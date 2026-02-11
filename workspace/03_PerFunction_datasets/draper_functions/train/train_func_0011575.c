opal_dss_unpack_byte(opal_buffer_t *buffer, void *dest,
                         int32_t *num_vals, opal_data_type_t type)
{
    OPAL_OUTPUT( ( opal_dss_verbose, "opal_dss_unpack_byte * %d\n", (int)*num_vals ) );

    if (opal_dss_too_small(buffer, *num_vals)) {
        return OPAL_ERR_UNPACK_READ_PAST_END_OF_BUFFER;
    }


    memcpy(dest, buffer->unpack_ptr, *num_vals);


    buffer->unpack_ptr += *num_vals;

    return OPAL_SUCCESS;
}
