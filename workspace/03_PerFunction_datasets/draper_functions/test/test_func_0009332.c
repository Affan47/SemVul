winarg0 (void)
{

    if (h_version == V6 && (short) zargs[0] == -3)
	return cwin;

    if (zargs[0] >= ((h_version == V6) ? 8 : 2))
	runtime_error (ERR_ILL_WIN);

    return zargs[0];

}
