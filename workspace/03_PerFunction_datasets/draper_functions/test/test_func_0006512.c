AddLocalGenerator(cmLocalGenerator *lg)
{
  this->LocalGenerators.push_back(lg);


  const char *numGenC =
    this->CMakeInstance->GetCacheManager()->GetCacheValue
    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS");

  if (!numGenC)
    {


    this->FirstTimeProgress += ((1.0f - this->FirstTimeProgress) /30.0f);
    if(this->FirstTimeProgress > 0.95f)
      {
      this->FirstTimeProgress = 0.95f;
      }
    this->CMakeInstance->UpdateProgress("Configuring",
                                        this->FirstTimeProgress);
    return;
    }

  int numGen = atoi(numGenC);
  float prog = 0.9f*static_cast<float>(this->LocalGenerators.size())/
    static_cast<float>(numGen);
  if (prog > 0.9f)
    {
    prog = 0.9f;
    }
  this->CMakeInstance->UpdateProgress("Configuring", prog);
}
