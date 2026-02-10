ComputeComponentCount(NodeList const& nl)
{
  int count = 2;
  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
    {
    if(cmTarget* target = this->EntryList[*ni].Target)
      {
      if(cmTarget::LinkInterface const* iface =
         target->GetLinkInterface(this->Config, this->HeadTarget))
        {
        if(iface->Multiplicity > count)
          {
          count = iface->Multiplicity;
          }
        }
      }
    }
  return count;
}
