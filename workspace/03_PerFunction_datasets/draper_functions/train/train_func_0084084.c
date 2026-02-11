AddDefaultExtraGenerators()
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
#if defined(_WIN32) && !defined(__CYGWIN__)

#endif

  this->AddExtraGenerator(cmExtraCodeBlocksGenerator::GetActualName(),
                          &cmExtraCodeBlocksGenerator::New);
  this->AddExtraGenerator(cmExtraSublimeTextGenerator::GetActualName(),
                          &cmExtraSublimeTextGenerator::New);

#ifdef CMAKE_USE_ECLIPSE
  this->AddExtraGenerator(cmExtraEclipseCDT4Generator::GetActualName(),
                          &cmExtraEclipseCDT4Generator::New);
#endif

#ifdef CMAKE_USE_KDEVELOP
  this->AddExtraGenerator(cmGlobalKdevelopGenerator::GetActualName(),
                          &cmGlobalKdevelopGenerator::New);


  this->ExtraGenerators[cmGlobalKdevelopGenerator::GetActualName()]
                                             = &cmGlobalKdevelopGenerator::New;
#endif

#endif
}
