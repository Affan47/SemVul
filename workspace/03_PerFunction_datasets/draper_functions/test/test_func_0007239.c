atkin_chunk_q3(char* chunk, llong lower, llong upper)
{
    llong range = upper - lower;

    llong delta = sqrt((lower) / 3);
    delta = delta / 10 * 10;

    for (unsigned i = 0; atkin_q3_x0[i] + atkin_q3_y0[i] > 0; ++i)
    {
        atkin_q3_visit(chunk, lower, range, atkin_q3_x0[i] + delta, atkin_q3_y0[i]);
    }
}
