talloc_autofree_context(void)
{
	if (autofree_context == NULL || *autofree_context != getpid()) {
		autofree_context = talloc(NULL, pid_t);
		*autofree_context = getpid();
		talloc_set_name_const(autofree_context, "autofree_context");

		talloc_set_destructor(autofree_context, talloc_autofree_destructor);
		atexit(talloc_autofree);
	}
	return autofree_context;
}
