Evaluate(const std::vector<std::string> &,
                       cmGeneratorExpressionContext *context,
                       const GeneratorExpressionContent *,
                       cmGeneratorExpressionDAGChecker *) const
  {
    context->HadContextSensitiveCondition = true;
    return context->Config ? context->Config : "";
  }
}
