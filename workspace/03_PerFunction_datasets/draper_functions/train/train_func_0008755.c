targetNameGenex(const char *lib)
{
  return std::string("$<TARGET_NAME:") + lib + ">";
}
