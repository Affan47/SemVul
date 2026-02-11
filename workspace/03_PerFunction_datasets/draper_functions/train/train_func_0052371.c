decreaseLeadsLags(int n) const
{
  switch (type)
    {
    case eEndogenous:
    case eExogenous:
    case eExogenousDet:
    case eTrend:
    case eLogTrend:
      return datatree.AddVariable(symb_id, lag-n);
    case eModelLocalVariable:
      return datatree.local_variables_table[symb_id]->decreaseLeadsLags(n);
    default:
      return const_cast<VariableNode *>(this);
    }
}
