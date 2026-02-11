replaceTrendVar() const
{
  if (get_type() == eTrend)
    return datatree.One;
  else if (get_type() == eLogTrend)
    return datatree.Zero;
  else
    return const_cast<VariableNode *>(this);
}
