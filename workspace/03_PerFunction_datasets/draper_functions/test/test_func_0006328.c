test_xfer_simple(void)
{
    unsigned int i;
    GSource *src;
    XferElement *elements[] = {
	xfer_source_random(100*1024, RANDOM_SEED),
	xfer_filter_xor('d'),
	xfer_filter_xor('d'),
	xfer_dest_null(RANDOM_SEED),
    };

    Xfer *xfer = xfer_new(elements, sizeof(elements)/sizeof(*elements));
    src = xfer_get_source(xfer);
    g_source_set_callback(src, (GSourceFunc)test_xfer_generic_callback, NULL, NULL);
    g_source_attach(src, NULL);
    tu_dbg("Transfer: %s\n", xfer_repr(xfer));


    for (i = 0; i < sizeof(elements)/sizeof(*elements); i++) {
	g_object_unref(elements[i]);
	g_assert(G_OBJECT(elements[i])->ref_count == 1);
	elements[i] = NULL;
    }

    xfer_start(xfer, 0, 0);

    g_main_loop_run(default_main_loop());
    g_assert(xfer->status == XFER_DONE);

    xfer_unref(xfer);

    return 1;
}
