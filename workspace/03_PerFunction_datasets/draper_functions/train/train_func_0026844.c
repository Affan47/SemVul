validate_label(st_data_t name, st_data_t label, st_data_t arg)
{
    rb_iseq_t *iseq = (rb_iseq_t *)arg;
    LABEL *lobj = (LABEL *)label;
    if (!lobj->link.next) {
	do {
	    int ret;
	    COMPILE_ERROR((ruby_sourcefile, lobj->position,
			   "%s: undefined label", rb_id2name((ID)name)));
	} while (0);
    }
    return ST_CONTINUE;
}
