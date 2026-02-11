single_test_basename(const char* input,
                     const char* expect) {

    const char* result(compat_basename(input));
    BOOST_CHECK_EQUAL(std::string(result), std::string(expect));
}
