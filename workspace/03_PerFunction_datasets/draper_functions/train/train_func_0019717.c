operator[](u_int16 i)
{
    if (in_table (i)) return *(glyphs[i]);
    else return *(glyphs[' ']);
}
