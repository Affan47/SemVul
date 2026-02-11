ParseClone(std::vector<std::string> args)
{
  this->Synchronizer->SetOperation(midasSynchronizer::OPERATION_CLONE);
  this->Synchronizer->SetRecursive(true);

  if(args.size())
    {
    this->Synchronizer->SetServerURL(args[0]);
    }
  else if(this->Synchronizer->GetServerURL() == "")
    {
    this->PrintCommandHelp("clone");
    return false;
    }
  return true;
}
