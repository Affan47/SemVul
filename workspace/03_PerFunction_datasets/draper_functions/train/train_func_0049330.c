rb_register_transcoder(const rb_transcoder *tr)
{
    const char *const sname = tr->src_encoding;
    const char *const dname = tr->dst_encoding;

    transcoder_entry_t *entry;

    entry = make_transcoder_entry(sname, dname);
    if (entry->transcoder) {
	rb_raise(rb_eArgError, "transcoder from %s to %s has been already registered",
		 sname, dname);
    }

    entry->transcoder = tr;
}
