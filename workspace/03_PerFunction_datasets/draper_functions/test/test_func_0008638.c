w_key2str(w_data *d, w_key *key, et_string_t *r_str)
{
    const char *kcname;
    repr_shifts(r_str, key);
    kcname = _keycode2string(d->_dpy, key->_code);
    if (kcname != NULL) {
	et_str_cat(r_str, kcname);
	return 0;
    } else {
	et_str_clear(r_str);
	return -1;
    }
}
