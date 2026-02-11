fdbm_fetch(VALUE obj, VALUE keystr, VALUE ifnone)
{
    datum key, value;
    struct dbmdata *dbmp;
    DBM *dbm;

    ExportStringValue(keystr);
    key.dptr = RSTRING_PTR(keystr);
    key.dsize = (int)RSTRING_LEN(keystr);

    GetDBM2(obj, dbmp, dbm);
    value = dbm_fetch(dbm, key);
    if (value.dptr == 0) {
	if (ifnone == Qnil && rb_block_given_p())
	    return rb_yield(rb_tainted_str_new(key.dptr, key.dsize));
	return ifnone;
    }
    return rb_tainted_str_new(value.dptr, value.dsize);
}
