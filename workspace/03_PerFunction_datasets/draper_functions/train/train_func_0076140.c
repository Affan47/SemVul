routesplinesterm()
{
    if (--routeinit > 0) return;
    free(ps);
#ifdef UNUSED
    free(bs), bs = NULL  ;
#endif
    if (Verbose)
	fprintf(stderr,
		"routesplines: %d edges, %d boxes %.2f sec\n",
		nedges, nboxes, elapsed_sec());
}
