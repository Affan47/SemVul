agmt_ptr_cmp(Object *ro, const void *arg)
{
	Repl_Agmt *ra;
	Repl_Agmt *provided_ra = (Repl_Agmt *)arg;

	ra = object_get_data(ro);

    if (ra == provided_ra)
        return 0;
    else
        return 1;
}
