c_sci_version(state_t *s)
{
	if (!s) {
		sciprintf("Not in debug state\n");
		return 1;
	}

	sciprintf("Emulating SCI version %d.%03d.%03d\n",
		  SCI_VERSION_MAJOR(s->version),
		  SCI_VERSION_MINOR(s->version),
		  SCI_VERSION_PATCHLEVEL(s->version));

	return 0;
}
