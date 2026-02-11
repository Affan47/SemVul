mdbChangeColumn(Edi *edi, cchar *tableName, cchar *columnName, int type, int flags)
{
    Mdb         *mdb;
    MdbTable    *table;
    MdbCol      *col;

    mprAssert(edi);
    mprAssert(tableName && *tableName);
    mprAssert(columnName && *columnName);
    mprAssert(type);

    mdb = (Mdb*) edi;
    lock(mdb);
    if ((table = lookupTable(mdb, tableName)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    if ((col = lookupColumn(table, columnName)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    col->name = sclone(columnName);
    col->type = type;
    autoSave(mdb, table);
    unlock(mdb);
    return 0;
}
