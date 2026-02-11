sechk_lib_compare_sev(const char *a, const char *b)
{
	int aval, bval;

	if (a == NULL || b == NULL) {
		assert(false);
		errno = EINVAL;
		return -1;
	}

	if (strcmp(a, SECHK_SEV_NONE) == 0)
		aval = 0;
	else if (strcmp(a, SECHK_SEV_LOW) == 0)
		aval = 1;
	else if (strcmp(a, SECHK_SEV_MED) == 0)
		aval = 2;
	else if (strcmp(a, SECHK_SEV_HIGH) == 0)
		aval = 3;
	else {
		assert(false);
		errno = EINVAL;
		return -1;
	}

	if (strcmp(b, SECHK_SEV_NONE) == 0)
		bval = 0;
	else if (strcmp(b, SECHK_SEV_LOW) == 0)
		bval = 1;
	else if (strcmp(b, SECHK_SEV_MED) == 0)
		bval = 2;
	else if (strcmp(b, SECHK_SEV_HIGH) == 0)
		bval = 3;
	else {
		assert(false);
		errno = EINVAL;
		return -1;
	}

	if (aval == bval)
		return 0;

	return aval < bval ? -1 : 1;
}
