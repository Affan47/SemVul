comment_test() {
    ojcVal		val;
    struct _ojcErr	err = OJC_ERR_INIT;
    const char		*json = "{\n\
  // a comment\n\
  \"a\":\"Alpha\",\n\
  // another comment\n\
  \"b\":true,\n\
  /* third comment */\n\
  \"c\":12345\n\
}";
    char		result[256];

    val = ojc_parse_str(&err, json, 0, 0);
    if (ut_handle_error(&err)) {
	return;
    }
    ojc_fill(&err, val, 0, result, sizeof(result) - 1);
    ut_same("{\"a\":\"Alpha\",\"b\":true,\"c\":12345}", result);
    ojc_destroy(val);
}
