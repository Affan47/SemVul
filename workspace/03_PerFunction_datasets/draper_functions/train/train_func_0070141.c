PrintFullTestCommentIfPresent(const TestInfo& test_info) {
  const char* const type_param = test_info.type_param();
  const char* const value_param = test_info.value_param();

  if (type_param != NULL || value_param != NULL) {
    printf(", where ");
    if (type_param != NULL) {
      printf("TypeParam = %s", type_param);
      if (value_param != NULL)
        printf(" and ");
    }
    if (value_param != NULL) {
      printf("GetParam() = %s", value_param);
    }
  }
}
