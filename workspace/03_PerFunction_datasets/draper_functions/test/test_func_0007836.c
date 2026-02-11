compare_costs (comp_cost cost1, comp_cost cost2)
{
  if (cost1.cost == cost2.cost)
    return cost1.complexity - cost2.complexity;

  return cost1.cost - cost2.cost;
}
