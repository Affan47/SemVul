execute()
{
  (*__pdeEquation).execute();
  (*__bcList).execute();

  __pdeProblem = new PDEProblem((*__pdeEquation).pde(),
				(*__bcList).boundaryConditionSet());
}
