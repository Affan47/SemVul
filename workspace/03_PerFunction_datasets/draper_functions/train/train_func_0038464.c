FollowLinkEntry(BFSEntry const& qe)
{

  int depender_index = qe.Index;
  LinkEntry const& entry = this->EntryList[depender_index];


  if(entry.Target)
    {

    if(cmTarget::LinkInterface const* iface =
       entry.Target->GetLinkInterface(this->Config))
      {

      this->AddLinkEntries(depender_index, iface->Libraries);


      this->QueueSharedDependencies(depender_index, iface->SharedDeps);


      for(std::vector<std::string>::const_iterator
            oi = iface->WrongConfigLibraries.begin();
          oi != iface->WrongConfigLibraries.end(); ++oi)
        {
        this->CheckWrongConfigItem(depender_index, *oi);
        }
      }
    }
  else
    {

    this->AddVarLinkEntries(depender_index, qe.LibDepends);
    }
}
