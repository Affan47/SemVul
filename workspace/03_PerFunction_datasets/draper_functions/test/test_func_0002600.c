cmd_get(const char *item)
{
	char *ret_value;
	char *ret_error;
	if (hdhomerun_device_get_var(hd, item, &ret_value, &ret_error) < 0) {
		fprintf(stderr, "communication error sending request to hdhomerun device\n");
		return -1;
	}

	if (ret_error) {
		printf("%s\n", ret_error);
		return 0;
	}

	printf("%s\n", ret_value);
	return 1;
}
