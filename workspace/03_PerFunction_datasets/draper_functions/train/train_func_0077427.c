InterpolateSolutionN(const VectorType & pt, const Solution & sol, unsigned int f,
                              unsigned int solutionIndex) const
{
  Float value = 0.0;

  VectorType   shapef = this->ShapeFunctions(pt);
  unsigned int Nnodes = this->GetNumberOfNodes();
  for( unsigned int n = 0; n < Nnodes; n++ )
    {
    value += shapef[n] * sol.GetSolutionValue(this->GetNode(n)->GetDegreeOfFreedom(f), solutionIndex);
    }
  return value;
}
