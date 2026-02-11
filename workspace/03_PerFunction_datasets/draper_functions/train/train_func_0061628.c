CreateComponentTest(const char* component)
{
  std::string result = "NOT CMAKE_INSTALL_COMPONENT OR "
    "\"${CMAKE_INSTALL_COMPONENT}\" STREQUAL \"";
  result += component;
  result += "\"";
  return result;
}
