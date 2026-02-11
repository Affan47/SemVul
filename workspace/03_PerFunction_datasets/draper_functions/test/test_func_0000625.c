cmpdi_read_i(InStream *is, uchar *b, int len)
{
    CompoundInStream *cis = is->d.cis;
    off_t start = is_pos(is);

    if ((start + len) > cis->length) {
        RAISE(EOF_ERROR, "Tried to read past end of file. File length is "
              "<%"F_OFF_T_PFX"d> and tried to read to <%"F_OFF_T_PFX"d>",
              cis->length, start + len);
    }

    is_seek(cis->sub, cis->offset + start);
    is_read_bytes(cis->sub, b, len);
}
