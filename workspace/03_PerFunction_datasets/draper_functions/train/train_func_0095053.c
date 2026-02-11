us_slip_decoder_parse( us_slip_decoder_t *self, const uint8_t *data, int data_len )
{
    int packet_count = 0;
    int i;
    for ( i = 0; i < data_len; ++i )
    {
        uint8_t c = data[i];
        switch ( self->m_state )
        {
        case us_slip_state_before_packet:

            if ( c == US_SLIP_END )
            {

                self->m_state = us_slip_state_in_packet;
            }
            break;
        case us_slip_state_in_packet:

            if ( c == US_SLIP_END && us_buffer_readable_count( self->m_buffer ) > 0 )
            {

                self->m_packet_formed_callback( self, self->m_buffer );

                us_buffer_reset( self->m_buffer );

                packet_count++;

            }
            else if ( c == US_SLIP_ESC )
            {

                self->m_state = us_slip_state_in_esc;
            }
            else
            {

                us_buffer_append_byte( self->m_buffer, c );
            }
            break;
        case us_slip_state_in_esc:
            if ( c == US_SLIP_ESC_END )
            {

                us_buffer_append_byte( self->m_buffer, US_SLIP_END );
                self->m_state = us_slip_state_in_packet;
            }
            else if ( c == US_SLIP_ESC_ESC )
            {

                us_buffer_append_byte( self->m_buffer, US_SLIP_ESC );
                self->m_state = us_slip_state_in_packet;
            }
            else
            {

                us_slip_decoder_reset( self );
            }
            break;
        default:

            us_slip_decoder_reset( self );
            break;
        }
    }
    return packet_count;
}
