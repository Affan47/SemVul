GetPolicyStatusInternal(cmPolicies::PolicyID id)
{

  for(PolicyStackType::reverse_iterator psi = this->PolicyStack.rbegin();
      psi != this->PolicyStack.rend(); ++psi)
    {
    PolicyStackEntry::const_iterator pse = psi->find(id);
    if(pse != psi->end())
      {
      return pse->second;
      }
    }


  if(this->LocalGenerator->GetParent())
    {
    cmMakefile* parent = this->LocalGenerator->GetParent()->GetMakefile();
    return parent->GetPolicyStatusInternal(id);
    }


  return this->GetPolicies()->GetPolicyStatus(id);
}
