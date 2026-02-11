parse_nsec3_params(knot_nsec3_params_t *params, const char *salt,
			       const char *algorithm, const char *iterations)
{
	int result;

	result = knot_str2uint8t(algorithm, &params->algorithm);
	if (result != KNOT_EOK) {
		fprintf(stderr, "Invalid algorithm number.\n");
		return false;
	}

	result = knot_str2uint16t(iterations, &params->iterations);
	if (result != KNOT_EOK) {
		fprintf(stderr, "Invalid iteration count: %s\n",
		        knot_strerror(result));
		return false;
	}

	size_t salt_length = 0;
	uint8_t *salt_data = NULL;

	if (salt[0] != '\0') {
		result = hex_decode(salt, &salt_data, &salt_length);
		if (result != KNOT_EOK) {
			fprintf(stderr, "Invalid salt: %s\n",
				knot_strerror(result));
			return false;
		}
	}

	if (salt_length > UINT8_MAX) {
		fprintf(stderr, "Invalid salt: Maximal length is %d bytes.\n",
		        UINT8_MAX);
		free(salt_data);
		return false;
	}

	params->salt = salt_data;
	params->salt_length = (uint8_t)salt_length;

	return true;
}
