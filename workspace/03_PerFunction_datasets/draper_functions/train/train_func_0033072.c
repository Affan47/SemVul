gfarm_auth_method_get_available(void)
{
	int i;
	gfarm_int32_t methods;

	assert(GFARM_AUTH_METHOD_NUMBER <= sizeof(gfarm_int32_t) * CHAR_BIT);

	methods = 0;
	for (i = GFARM_AUTH_METHOD_NONE + 1; i < GFARM_AUTH_METHOD_NUMBER;
	    i++) {
		switch (i) {
		case GFARM_AUTH_METHOD_GSI_OLD:
			break;
#ifndef HAVE_GSI
		case GFARM_AUTH_METHOD_GSI:
			break;
		case GFARM_AUTH_METHOD_GSI_AUTH:
			break;
#endif
		default:
			methods |= 1 << i;
			break;
		}
	}
	return (methods);
}
