Evaluate(
                            cmGeneratorExpressionContext *context,
                            cmGeneratorExpressionDAGChecker *dagChecker) const
{
  std::string identifier;
  {
  std::vector<cmGeneratorExpressionEvaluator*>::const_iterator it
                                          = this->IdentifierChildren.begin();
  const std::vector<cmGeneratorExpressionEvaluator*>::const_iterator end
                                          = this->IdentifierChildren.end();
  for ( ; it != end; ++it)
    {
    identifier += (*it)->Evaluate(context, dagChecker);
    if (context->HadError)
      {
      return std::string();
      }
    }
  }

  const cmGeneratorExpressionNode *node = GetNode(identifier);

  if (!node)
    {
    reportError(context, this->GetOriginalExpression(),
              "Expression did not evaluate to a known generator expression");
    return std::string();
    }

  if (!node->GeneratesContent())
    {
    if (node->NumExpectedParameters() == 1
        && node->AcceptsArbitraryContentParameter())
      {
      if (this->ParamChildren.empty())
        {
        reportError(context, this->GetOriginalExpression(),
                  "$<" + identifier + "> expression requires a parameter.");
        }
      }
    else
      {
      std::vector<std::string> parameters;
      this->EvaluateParameters(node, identifier, context, dagChecker,
                               parameters);
      }
    return std::string();
    }

  if (node->NumExpectedParameters() == 1
        && node->AcceptsArbitraryContentParameter())
    {
    return this->ProcessArbitraryContent(node, identifier, context,
                                         dagChecker,
                                         this->ParamChildren.begin());
    }

  std::vector<std::string> parameters;
  this->EvaluateParameters(node, identifier, context, dagChecker, parameters);
  if (context->HadError)
    {
    return std::string();
    }

  return node->Evaluate(parameters, context, this, dagChecker);
}
