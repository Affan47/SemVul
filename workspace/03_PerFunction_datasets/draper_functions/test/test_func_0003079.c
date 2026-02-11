new_cgats_al(
cgatsAlloc *al
) {
	cgats *p;

	if ((p = (cgats *) al->calloc(al, sizeof(cgats), 1)) == NULL) {
		return NULL;
	}
	p->al = al;


	p->find_kword = find_kword;
	p->find_field = find_field;
	p->read       = cgats_read;
	p->add_table  = add_table;
	p->set_table_flags = set_table_flags;
	p->set_cgats_type  = set_cgats_type;
	p->add_other  = add_other;
	p->get_oi     = get_oi;
	p->add_kword  = add_kword;
	p->add_field  = add_field;
	p->add_set    = add_set;
	p->add_setarr = add_setarr;
	p->get_setarr = get_setarr;
	p->write      = cgats_write;
	p->error      = cgats_error;
	p->del        = cgats_del;

#ifndef SEPARATE_STD
	p->read_name  = cgats_read_name;
	p->write_name = cgats_write_name;
#else
	p->read_name  = NULL;
	p->write_name = NULL;
#endif

	return p;
}
