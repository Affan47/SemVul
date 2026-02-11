sqlite_db_secondary_open(DB *prim, DB **sdb, char *fname, u_int32_t pagesize,
                             u_int32_t dup_flag, int(*callback)(DB*, const DBT*, const DBT*, DBT*),
                             int(*compare)(DB*, const DBT*, const DBT*)){
    int ret=0;
    ret = db_create(sdb, dbenv, 0);
    ret = (*sdb)->set_pagesize(*sdb, pagesize);
    if(dup_flag)
        ret = (*sdb)->set_flags(*sdb, dup_flag);
    if(compare != NULL)
        ret = (*sdb)->set_dup_compare(*sdb, compare);
    ret = (*sdb)->open(*sdb, NULL, fname, NULL, DB_BTREE, DB_CREATE, 0);
    ret = (*sdb)->associate(prim, NULL, *sdb, callback, DB_CREATE);

    return(0);
}
