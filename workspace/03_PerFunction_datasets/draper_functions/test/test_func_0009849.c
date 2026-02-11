obj_cvs(const gs_memory_t *mem, const ref * op, byte * str, uint len, uint * prlen,
        const byte ** pchars)
{
    int code = obj_cvp(op, str, len, prlen, 0, 0, mem, false);

    if (code == 1) {
        if (pchars)
            obj_string_data(mem, op, pchars, prlen);
        return gs_note_error(e_rangecheck);
    } else {
        if (pchars)
          *pchars = str;
        return code;
    }
}
