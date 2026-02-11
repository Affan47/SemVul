plot_write_tests(
	unsigned int num_results,
	const struct exp_result_t *results,
	FILE *output,
	bool success
)
{
	unsigned int ret = 0;
	unsigned int i;

	for (i = 0; i < num_results; i++) {
		if (results[i].success != success) {
			continue;
		}


		if (results[i].runtime >= 5) {
			fprintf(output, "%s %f\n", results[i].timestamp,
				results[i].runtime / 60.0);
			ret++;
		}
	}

	return ret;
}
