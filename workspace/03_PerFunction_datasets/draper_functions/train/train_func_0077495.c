mdbUpdateField(Edi *edi, cchar *tableName, cchar *key, cchar *fieldName, cchar *value)
{
    Mdb         *mdb;
    MdbTable    *table;
    MdbRow      *row;
    MdbCol      *col;
    int         r;

    mdb = (Mdb*) edi;
    lock(mdb);
    if ((table = lookupTable(mdb, tableName)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    if ((col = lookupColumn(table, fieldName)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    if ((r = lookupRow(table, key)) < 0) {
        row = createRow(mdb, table);
    }
    if ((row = getRow(table, r)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    updateFieldValue(row, col, value);
    unlock(mdb);
    return 0;
}
