tmp_dh_cb(SSL *s UNUSED, int export UNUSED, int keylength)
{
	DH *r = NULL;
	static DH *dh = NULL;
	static DH *dh512 = NULL;
	static DH *dh1024 = NULL;
	static DH *dh2048 = NULL;
	static DH *dh4096 = NULL;

	switch (keylength)
	{
	case 512:
		if (dh512 == NULL)
			dh512 = load_dh_buffer(file_dh512, sizeof file_dh512);
		r = dh512;
		break;
	case 1024:
		if (dh1024 == NULL)
			dh1024 = load_dh_buffer(file_dh1024, sizeof file_dh1024);
		r = dh1024;
		break;
	case 2048:
		if (dh2048 == NULL)
			dh2048 = load_dh_buffer(file_dh2048, sizeof file_dh2048);
		r = dh2048;
		break;
	case 4096:
		if (dh4096 == NULL)
			dh4096 = load_dh_buffer(file_dh4096, sizeof file_dh4096);
		r = dh4096;
		break;
	default:


		dh = DH_generate_parameters(keylength, DH_GENERATOR_2, NULL, NULL);
		r = dh;
	}

	return r;
}
