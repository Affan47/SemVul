getivar(const char *varname)
{
    struct udvt_entry *udv_ptr = first_udv;

    while (udv_ptr) {
	if (!strcmp(varname, udv_ptr->udv_name))
	    return udv_ptr->udv_value.type == INTGR
		? udv_ptr->udv_value.v.int_val
		: 0;
	udv_ptr = udv_ptr->next_udv;
    }
    return 0;
}
