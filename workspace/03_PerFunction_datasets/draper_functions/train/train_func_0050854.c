parse_as_count_loop (LOOPSET *loop,
				DATASET *dset,
				const char *s)
{
    int err;

    err = index_get_limit(loop, &loop->final, s, dset);

    if (!err) {
	loop->init.val = 1;
	loop->type = COUNT_LOOP;
    }

#if LOOP_DEBUG
    fprintf(stderr, "parse_as_count_loop: init.val=%g, final.val=%g\n",
	    loop->init.val, loop->final.val);
#endif

    return err;
}
