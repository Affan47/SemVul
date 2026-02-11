QueueDependencies(cmSourceFile* sf)
{

  if(const char* additionalDeps = sf->GetProperty("OBJECT_DEPENDS"))
    {
    std::vector<std::string> objDeps;
    cmSystemTools::ExpandListArgument(additionalDeps, objDeps);
    this->QueueOnce(objDeps);
    }


  this->QueueOnce(sf->GetDepends());


  if(cmCustomCommand const* cc = sf->GetCustomCommand())
    {
    this->CheckCustomCommand(*cc);
    }

}
