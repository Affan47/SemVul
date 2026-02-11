DefinePolicy(cmPolicies::PolicyID iD,
                              const char *idString,
                              const char *shortDescription,
                              const char *longDescription,
                              unsigned int majorVersionIntroduced,
                              unsigned int minorVersionIntroduced,
                              unsigned int patchVersionIntroduced,
                              unsigned int tweakVersionIntroduced,
                              cmPolicies::PolicyStatus status)
{

  if (this->Policies.find(iD) != this->Policies.end())
  {
    cmSystemTools::Error("Attempt to redefine a CMake policy for policy "
      "ID ", this->GetPolicyIDString(iD).c_str());
    return;
  }

  this->Policies[iD] = new cmPolicy(iD, idString,
                                    shortDescription,
                                    longDescription,
                                    majorVersionIntroduced,
                                    minorVersionIntroduced,
                                    patchVersionIntroduced,
                                    tweakVersionIntroduced,
                                    status);
  this->PolicyStringMap[idString] = iD;
}
