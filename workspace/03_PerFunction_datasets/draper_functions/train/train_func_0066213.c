mdbRemoveIndex(Edi *edi, cchar *tableName, cchar *indexName)
{
    Mdb         *mdb;
    MdbTable    *table;

    mdb = (Mdb*) edi;
    lock(mdb);
    if ((table = lookupTable(mdb, tableName)) == 0) {
        unlock(mdb);
        return MPR_ERR_CANT_FIND;
    }
    table->index = 0;
    if (table->indexCol) {
        table->indexCol->flags &= ~EDI_INDEX;
        table->indexCol = 0;
        autoSave(mdb, table);
    }
    unlock(mdb);
    return 0;
}
