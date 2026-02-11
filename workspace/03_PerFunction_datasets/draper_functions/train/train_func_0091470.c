get_affected_vars(std::set<ushort_t>* setAffectedVars)const
{
  for (size_t i = 0; i < effect().size(); i++)
    {
      effect().effect(i)->get_affected_vars(setAffectedVars);
    }
}
