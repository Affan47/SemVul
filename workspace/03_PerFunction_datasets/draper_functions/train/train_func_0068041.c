Evaluate(const std::vector<std::string> &parameters,
                       cmGeneratorExpressionContext *context,
                       const GeneratorExpressionContent *content,
                       cmGeneratorExpressionDAGChecker *dagChecker) const
  {
    if (parameters.size() != 0 && parameters.size() != 1)
      {
      reportError(context, content->GetOriginalExpression(),
          "$<C_COMPILER_ID> expression requires one or two parameters");
      return std::string();
      }
    if (!context->HeadTarget)
      {
      reportError(context, content->GetOriginalExpression(),
          "$<C_COMPILER_ID> may only be used with targets.  It may not "
          "be used with add_custom_command.");
      }
    return this->EvaluateWithLanguage(parameters, context, content,
                                      dagChecker, "C");
  }
