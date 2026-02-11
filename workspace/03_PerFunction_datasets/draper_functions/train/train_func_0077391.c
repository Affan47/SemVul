consolidate_set_function (GnmConsolidate *cs, GnmFunc *fd)
{
	g_return_if_fail (cs != NULL);
	g_return_if_fail (fd != NULL);

	if (cs->fd)
		gnm_func_unref (cs->fd);

	cs->fd = fd;
	gnm_func_ref (fd);
}
