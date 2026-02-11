AddLibrary(const char* lname, cmTarget::TargetType type,
                            const std::vector<std::string> &srcs,
                            bool excludeFromAll)
{

  if (    (type != cmTarget::STATIC_LIBRARY)
       && (type != cmTarget::SHARED_LIBRARY)
       && (type != cmTarget::MODULE_LIBRARY))
    {
    type = cmTarget::STATIC_LIBRARY;
    }

  cmTarget* target = this->AddNewTarget(type, lname);


  target->ClearDependencyInformation( *this, lname );
  if(excludeFromAll)
    {
    target->SetProperty("EXCLUDE_FROM_ALL", "TRUE");
    }
  target->AddSources(srcs);
  this->AddGlobalLinkInformation(lname, *target);
}
