rb_mod_const_at(VALUE mod, void *data)
{
    st_table *tbl = data;
    if (!tbl) {
	tbl = st_init_numtable();
    }
    if (RCLASS_CONST_TBL(mod)) {
	st_foreach_safe(RCLASS_CONST_TBL(mod), sv_i, (st_data_t)tbl);
    }
    return tbl;
}
