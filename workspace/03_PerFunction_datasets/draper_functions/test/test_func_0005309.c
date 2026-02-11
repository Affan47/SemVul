RecordPolicies(cmPolicies::PolicyMap& pm)
{

  typedef cmPolicies::PolicyID PolicyID;
  for(PolicyID pid = cmPolicies::CMP0000;
      pid != cmPolicies::CMPCOUNT; pid = PolicyID(pid+1))
    {
    pm[pid] = this->GetPolicyStatus(pid);
    }
}
