run( TestResult &controller,
                 const std::string &testPath )
{
  TestPath path = m_suite->resolveTestPath( testPath );
  Test *testToRun = path.getChildTest();

  controller.runTest( testToRun );
}
