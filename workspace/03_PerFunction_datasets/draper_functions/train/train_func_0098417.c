fileExists(const std::string & fileName) {
  std::ifstream fileTest(fileName.c_str());

  if (!fileTest)
    return false;

  fileTest.close();
  return true;
}
