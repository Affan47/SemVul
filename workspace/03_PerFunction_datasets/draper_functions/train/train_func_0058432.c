IsPolicyNewerThan(unsigned int majorV,
                         unsigned int minorV,
                         unsigned int patchV,
                         unsigned int tweakV)
  {
    if (majorV < this->MajorVersionIntroduced)
    {
      return true;
    }
    if (majorV > this->MajorVersionIntroduced)
    {
      return false;
    }
    if (minorV < this->MinorVersionIntroduced)
    {
      return true;
    }
    if (minorV > this->MinorVersionIntroduced)
    {
      return false;
    }
    if (patchV < this->PatchVersionIntroduced)
    {
      return true;
    }
    if (patchV > this->PatchVersionIntroduced)
    {
      return false;
    }
    return (tweakV < this->TweakVersionIntroduced);
  }
