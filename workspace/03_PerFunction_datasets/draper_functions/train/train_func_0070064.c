aappend_test() {
    char		actual[256];
    ojcVal		val;
    struct _ojcErr	err = OJC_ERR_INIT;
    const char		*json = "{\"zero\":0,\"one\":{\"1\":true,\"2\":null},\"two\":2}";
    const char		*expect = "{\"zero\":0,\"one\":{\"1\":true,\"2\":null,\"3\":true,\"3\":false},\"two\":2,\"three\":3}";
    const char		*path[3] = { 0, 0, 0 };

    val = ojc_parse_str(&err, json, 0, 0);
    if (ut_handle_error(&err)) {
	return;
    }
    path[0] = "three";
    ojc_aappend(&err, val, path, ojc_create_int(3));
    path[0] = "one";
    path[1] = "3";
    ojc_aappend(&err, val, path, ojc_create_bool(true));
    ojc_aappend(&err, val, path, ojc_create_bool(false));
    ojc_fill(&err, val, 0, actual, sizeof(actual));
    if (ut_handle_error(&err)) {
	return;
    }
    ut_same(expect, actual);
}
