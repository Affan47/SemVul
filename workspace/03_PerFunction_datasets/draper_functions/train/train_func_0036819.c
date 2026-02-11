AddEvaluationFile(const std::string &inputFile,
                    cmsys::auto_ptr<cmCompiledGeneratorExpression> outputExpr,
                    cmMakefile *makefile,
                    cmsys::auto_ptr<cmCompiledGeneratorExpression> condition,
                    bool inputIsContent)
{
  this->EvaluationFiles.push_back(
              new cmGeneratorExpressionEvaluationFile(inputFile, outputExpr,
                                                      makefile, condition,
                                                      inputIsContent));
}
