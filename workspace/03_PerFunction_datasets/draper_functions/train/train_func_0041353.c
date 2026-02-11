encode_row(t4_state_t *s)
{
    switch (s->line_encoding)
    {
    case T4_COMPRESSION_ITU_T6:


        if (s->row_bits)
            update_row_bit_info(s);
        encode_2d_row(s);
        break;
    case T4_COMPRESSION_ITU_T4_2D:
        encode_eol(s);
        if (s->row_is_2d)
        {
            encode_2d_row(s);
            s->rows_to_next_1d_row--;
        }
        else
        {
            encode_1d_row(s);
            s->row_is_2d = TRUE;
        }
        if (s->rows_to_next_1d_row <= 0)
        {

            s->row_is_2d = FALSE;
            s->rows_to_next_1d_row = s->max_rows_to_next_1d_row - 1;
        }
        break;
    default:
    case T4_COMPRESSION_ITU_T4_1D:
        encode_eol(s);
        encode_1d_row(s);
        break;
    }
    s->row++;
    return 0;
}
