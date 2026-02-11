us_osc_msg_element_d_flatten( const us_osc_msg_element_t *self_, us_buffer_t *buf, int32_t *total_length )
{
    bool r = true;
    us_osc_msg_element_d_t *self = (us_osc_msg_element_d_t *)self_;
    int32_t start_length = (int32_t)us_buffer_readable_count( buf );
    r &= us_buffer_append_float64( buf, self->m_value );
    if ( total_length )
    {
        *total_length = (int32_t)us_buffer_readable_count( buf ) - start_length;
    }
    return r;
}
