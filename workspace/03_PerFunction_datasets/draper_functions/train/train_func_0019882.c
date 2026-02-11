ranlib_main() {
  if (RestOfArgs.size() != 1)
    fail(ToolName + "takes just one archive as argument");
  ArchiveName = RestOfArgs[0];
  return performOperation(CreateSymTab, nullptr);
}
