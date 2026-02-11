_jobcomp_script_strerror (int errnum)
{
	struct jobcomp_errno *ep = errno_table;

	while ((ep->n != errnum) && (ep->n != -1))
		ep++;

	return (ep->descr);
}
