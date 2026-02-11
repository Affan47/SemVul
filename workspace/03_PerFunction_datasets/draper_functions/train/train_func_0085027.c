flipModel()
{
  if (parentModel_)
    return;

  double cutoff=getCutoff();
  flipSolver(referenceSolver_,cutoff);
  flipSolver(continuousSolver_,cutoff);
  flipSolver(solver_,cutoff);
}
