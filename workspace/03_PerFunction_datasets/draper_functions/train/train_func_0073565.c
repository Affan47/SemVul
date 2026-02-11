fdbm_has_key(VALUE obj, VALUE keystr)
{
    datum key, val;
    struct dbmdata *dbmp;
    DBM *dbm;

    ExportStringValue(keystr);
    key.dptr = RSTRING_PTR(keystr);
    key.dsize = (int)RSTRING_LEN(keystr);

    GetDBM2(obj, dbmp, dbm);
    val = dbm_fetch(dbm, key);
    if (val.dptr) return Qtrue;
    return Qfalse;
}
