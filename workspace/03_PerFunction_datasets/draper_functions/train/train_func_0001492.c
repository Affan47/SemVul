us_midi_parser_parse( us_midi_parser_t *self, uint8_t b, us_midi_msg_t *msg )
{


    us_midi_msg_init( msg );
    if ( b & 0x80 )
    {


        uint8_t status = ( uint8_t )( b & 0xf0 );
        if ( status == 0xf0 )
        {


            return us_midi_parser_system_byte( self, b, msg );
        }
        else
        {


            us_midi_parser_status_byte( self, b, msg );
            return false;
        }
    }
    else
    {


        return us_midi_parser_data_byte( self, b, msg );
    }
}
