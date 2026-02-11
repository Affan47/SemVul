octstr_insert_data(Octstr *ostr, long pos, const char *data, long len)
{
    seems_valid(ostr);
    gw_assert(!ostr->immutable);
    gw_assert(pos <= ostr->len);

    if (len == 0)
        return;

    octstr_grow(ostr, ostr->len + len);
    if (ostr->len > pos) {
        memmove(ostr->data + pos + len, ostr->data + pos, ostr->len - pos);
    }
    memcpy(ostr->data + pos, data, len);
    ostr->len += len;
    ostr->data[ostr->len] = '\0';

    seems_valid(ostr);
}
