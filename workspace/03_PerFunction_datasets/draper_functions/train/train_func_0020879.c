CuAssert_Line(CuTest* tc, const char* file, int line,
                   const char* message, int condition) {
	if (condition) return;
	CuFail_Line(tc, file, line, NULL, message);
}
