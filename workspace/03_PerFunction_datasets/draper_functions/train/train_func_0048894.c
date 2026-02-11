rb_econv_add_converter(rb_econv_t *ec, const char *sname, const char *dname, int n)
{
    transcoder_entry_t *entry;
    const rb_transcoder *tr;

    if (ec->started != 0)
        return -1;

    entry = get_transcoder_entry(sname, dname);
    if (!entry)
        return -1;

    tr = load_transcoder_entry(entry);
    if (!tr) return -1;

    return rb_econv_add_transcoder_at(ec, tr, n);
}
