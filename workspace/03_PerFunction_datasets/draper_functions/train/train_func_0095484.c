file_parse_test() {
    FILE		*f = fopen("tmp.json", "w");
    char		result[300];
    struct _ojcErr	err;
    ojcVal		val;

    fwrite(bench_json, sizeof(bench_json) - 1, 1, f);
    fclose(f);

    ojc_err_init(&err);
    f = fopen("tmp.json", "r");
    val = ojc_parse_stream(&err, f, 0, 0);
    fclose(f);
    if (ut_handle_error(&err)) {
	return;
    }
    ojc_fill(&err, val, 0, result, sizeof(result));

    ut_same(bench_json, result);
}
