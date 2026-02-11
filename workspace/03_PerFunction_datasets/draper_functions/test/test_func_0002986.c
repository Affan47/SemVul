xylist_write_field(xylist_t* ls, starxy_t* fld) {
    int i;
	assert(is_writing(ls));
    assert(fld);
    for (i=0; i<fld->N; i++) {
        if (fitstable_write_row(ls->table, fld->x + i, fld->y + i,
                                ls->include_flux ? fld->flux + i : NULL,
                                ls->include_background ? fld->background + i : NULL))
            return -1;
    }
    return 0;
}
