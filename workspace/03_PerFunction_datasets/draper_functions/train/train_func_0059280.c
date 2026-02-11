fsdbm_shift(VALUE obj)
{
    datum key, val;
    struct dbmdata *dbmp;
    DBM *dbm;
    VALUE keystr, valstr;

    fdbm_modify(obj);
    GetDBM2(obj, dbmp, dbm);
    key = sdbm_firstkey(dbm);
    if (!key.dptr) return Qnil;
    val = sdbm_fetch(dbm, key);
    keystr = rb_external_str_new(key.dptr, key.dsize);
    valstr = rb_external_str_new(val.dptr, val.dsize);
    sdbm_delete(dbm, key);
    if (dbmp->di_size >= 0) {
	dbmp->di_size--;
    }

    return rb_assoc_new(keystr, valstr);
}
