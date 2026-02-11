CheckComponents(cmComputeComponentGraph const& ccg)
{


  std::vector<NodeList> const& components = ccg.GetComponents();
  int nc = static_cast<int>(components.size());
  for(int c=0; c < nc; ++c)
    {

    NodeList const& nl = components[c];


    if(nl.size() < 2)
      {
      continue;
      }


    if(this->NoCycles)
      {
      this->ComplainAboutBadComponent(ccg, c);
      return false;
      }


    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      if(this->Targets[*ni]->GetType() != cmTarget::STATIC_LIBRARY)
        {
        this->ComplainAboutBadComponent(ccg, c);
        return false;
        }
      }
    }
  return true;
}
