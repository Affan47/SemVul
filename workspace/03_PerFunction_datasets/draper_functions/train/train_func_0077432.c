EvaluateWithLanguage(const std::vector<std::string> &parameters,
                       cmGeneratorExpressionContext *context,
                       const GeneratorExpressionContent *content,
                       cmGeneratorExpressionDAGChecker *,
                       const std::string &lang) const
  {
    const char *compilerId = context->Makefile ?
                              context->Makefile->GetSafeDefinition((
                              "CMAKE_" + lang + "_COMPILER_ID").c_str()) : "";
    if (parameters.size() == 0)
      {
      return compilerId ? compilerId : "";
      }
    cmsys::RegularExpression compilerIdValidator;
    compilerIdValidator.compile("^[A-Za-z0-9_]*$");
    if (!compilerIdValidator.find(parameters.begin()->c_str()))
      {
      reportError(context, content->GetOriginalExpression(),
                  "Expression syntax not recognized.");
      return std::string();
      }
    if (!compilerId)
      {
      return parameters.front().empty() ? "1" : "0";
      }

    if (cmsysString_strcasecmp(parameters.begin()->c_str(), compilerId) == 0)
      {
      return "1";
      }
    return "0";
  }
