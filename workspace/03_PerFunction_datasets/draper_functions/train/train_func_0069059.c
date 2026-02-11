PopulateCustomVectors(cmMakefile *mf)
{
  this->CTest->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_MATCH",
                             this->CustomErrorMatches);
  this->CTest->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_EXCEPTION",
                             this->CustomErrorExceptions);
  this->CTest->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_MATCH",
                             this->CustomWarningMatches);
  this->CTest->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_EXCEPTION",
                             this->CustomWarningExceptions);
  this->CTest->PopulateCustomInteger(mf,
                          "CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS",
                          this->MaxErrors);
  this->CTest->PopulateCustomInteger(mf,
                             "CTEST_CUSTOM_MAXIMUM_NUMBER_OF_WARNINGS",
                             this->MaxWarnings);

  int n = -1;
  this->CTest->PopulateCustomInteger(mf, "CTEST_CUSTOM_ERROR_PRE_CONTEXT", n);
  if (n != -1)
    {
    this->MaxPreContext = static_cast<size_t>(n);
    }

  n = -1;
  this->CTest->PopulateCustomInteger(mf, "CTEST_CUSTOM_ERROR_POST_CONTEXT", n);
  if (n != -1)
    {
    this->MaxPostContext = static_cast<size_t>(n);
    }


  if(const char* customWarningMatchers =
     mf->GetDefinition("CTEST_CUSTOM_WARNING_MATCH"))
    {
    cmSystemTools::ExpandListArgument(customWarningMatchers,
                                      this->ReallyCustomWarningMatches);
    }
  if(const char* customWarningExceptions =
     mf->GetDefinition("CTEST_CUSTOM_WARNING_EXCEPTION"))
    {
    cmSystemTools::ExpandListArgument(customWarningExceptions,
                                      this->ReallyCustomWarningExceptions);
    }
}
