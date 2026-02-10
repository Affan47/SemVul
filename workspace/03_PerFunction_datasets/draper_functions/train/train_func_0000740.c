xtransformer_write(transformer_state_t *xstate, const void *buf, size_t bufsize)
{
	ssize_t nwrote = transformer_write(xstate, buf, bufsize);
	if (nwrote != (ssize_t)bufsize) {
		xfunc_die();
	}
	return nwrote;
}
