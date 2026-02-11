rlm_perl_close_handles(void **handles)
{
	int i;

	if (!handles) {
		return;
	}

	for (i=0; handles[i]; i++) {
		radlog(L_DBG, "close %p\n", handles[i]);
		dlclose(handles[i]);
	}

	free(handles);
}
