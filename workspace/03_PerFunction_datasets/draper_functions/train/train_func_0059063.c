auth_mgr_final()
{
	UINT32 i;


	for (i = 0; i < auth_mgr.overflow_size; i++) {
		if (auth_mgr.overflow[i] != NULL)
			COND_SIGNAL(auth_mgr.overflow[i]);
	}

	free(auth_mgr.overflow);
	free(auth_mgr.auth_mapper);

	return TSS_SUCCESS;
}
