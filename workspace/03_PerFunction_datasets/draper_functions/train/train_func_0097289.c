do_map(Var key, Var value, void *data, int first)
{
    struct do_map_closure *dmc = (struct do_map_closure *)data;

    dmc->status = generate_key(dmc->g, key, dmc->gctx);
    if (yajl_gen_status_ok != dmc->status)
	return 1;
    dmc->status = generate(dmc->g, value, dmc->gctx);
    if (yajl_gen_status_ok != dmc->status)
	return 1;

    return 0;
}
