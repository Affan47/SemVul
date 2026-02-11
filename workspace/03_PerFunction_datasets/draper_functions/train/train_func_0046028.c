main(int argc, const char *argv[]) {
  JsonTest::Runner runner;
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, checkNormalizeFloatingPointStr);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, memberCount);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, objects);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, arrays);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, null);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, strings);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, bools);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, integers);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, nonIntegers);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareNull);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareInt);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareUInt);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareDouble);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareString);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareBoolean);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareArray);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareObject);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, compareType);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, checkInteger);
  JSONTEST_REGISTER_FIXTURE(runner, ValueTest, offsetAccessors);

  JSONTEST_REGISTER_FIXTURE(runner, ReaderTest, parseWithNoErrors);
  JSONTEST_REGISTER_FIXTURE(
      runner, ReaderTest, parseWithNoErrorsTestingOffsets);
  JSONTEST_REGISTER_FIXTURE(runner, ReaderTest, parseWithOneError);
  JSONTEST_REGISTER_FIXTURE(runner, ReaderTest, parseChineseWithOneError);
  JSONTEST_REGISTER_FIXTURE(runner, ReaderTest, parseWithDetailError);

  JSONTEST_REGISTER_FIXTURE(runner, WriterTest, dropNullPlaceholders);
  return runner.runCommandLine(argc, argv);
}
