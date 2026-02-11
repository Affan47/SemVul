MTX_BITIO_input_bit( register BITIO *t )
{

    if ( t->input_bit_count-- == 0 ) {
        t->input_bit_buffer = t->mem_bytes[ t->mem_index++ ];
        if ( t->mem_index > t->mem_size ) {
            longjmp( t->mem->env, ERR_BITIO_end_of_file );
        }
        ++(t->bytes_in);
        t->input_bit_count = 7;
    }
    t->input_bit_buffer <<= 1;
    return(t->input_bit_buffer & 0x100);
}
