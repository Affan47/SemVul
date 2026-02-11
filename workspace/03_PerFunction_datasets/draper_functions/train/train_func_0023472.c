numhash_init(VALUE self)
{
    st_table *tbl = (st_table *)DATA_PTR(self);
    if (tbl) st_free_table(tbl);
    DATA_PTR(self) = st_init_numtable();
    return self;
}
