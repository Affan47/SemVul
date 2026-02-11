set_success(
	const char *prefix,
	const char *experiment,
	const char *test_run,
	const char *filename,
	struct exp_result_t *dest
)
{
	if (strcmp(filename, "test.success") == 0) {
		dest->success = true;
	}
}
