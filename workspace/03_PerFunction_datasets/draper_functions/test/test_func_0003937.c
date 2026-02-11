R_DrawMaskedColumn(column_t * column, signed int baseclip)
{
    int topscreen, bottomscreen;
    fixed_t basetexturemid;

    basetexturemid = dc_texturemid;

    for (; column->topdelta != 0xff;)
    {

        topscreen = sprtopscreen + spryscale * column->topdelta;
        bottomscreen = topscreen + spryscale * column->length;
        dc_yl = (topscreen + FRACUNIT - 1) >> FRACBITS;
        dc_yh = (bottomscreen - 1) >> FRACBITS;

        if (dc_yh >= mfloorclip[dc_x])
            dc_yh = mfloorclip[dc_x] - 1;
        if (dc_yl <= mceilingclip[dc_x])
            dc_yl = mceilingclip[dc_x] + 1;

        if (dc_yh >= baseclip && baseclip != -1)
            dc_yh = baseclip;

        if (dc_yl <= dc_yh)
        {
            dc_source = (byte *) column + 3;
            dc_texturemid = basetexturemid - (column->topdelta << FRACBITS);

            colfunc();
        }
        column = (column_t *) ((byte *) column + column->length + 4);
    }

    dc_texturemid = basetexturemid;
}
