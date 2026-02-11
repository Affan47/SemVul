parseAndSaveValueTree(const std::string &input,
                                 const std::string &actual,
                                 const std::string &kind,
                                 Json::Value &root,
                                 const Json::Features &features,
                                 bool parseOnly) {
  Json::Reader reader(features);
  bool parsingSuccessful = reader.parse(input, root);
  if (!parsingSuccessful) {
    printf("Failed to parse %s file: \n%s\n",
           kind.c_str(),
           reader.getFormattedErrorMessages().c_str());
    return 1;
  }

  if (!parseOnly) {
    FILE *factual = fopen(actual.c_str(), "wt");
    if (!factual) {
      printf("Failed to create %s actual file.\n", kind.c_str());
      return 2;
    }
    printValueTree(factual, root);
    fclose(factual);
  }
  return 0;
}
