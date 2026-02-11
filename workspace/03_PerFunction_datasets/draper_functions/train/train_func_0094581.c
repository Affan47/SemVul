test_suite_4() {
    const char *filename = "tests/test_2.txt";
    JSON_Value *a = NULL, *a_copy = NULL;
    printf("Testing %s:\n", filename);
    a = json_parse_file(filename);
    TEST(json_value_equals(a, a));
    a_copy = json_value_deep_copy(a);
    TEST(a_copy != NULL);
    TEST(json_value_equals(a, a_copy));
}
