solution(double & solutionValue,
                           double * betterSolution)
{
    int nodeCount = model_->getNodeCount();
    if (feasibilityPumpOptions_>0 && (nodeCount % feasibilityPumpOptions_) != 0)
        return 0;
#ifdef DIVE_DEBUG
    std::cout << "solutionValue = " << solutionValue << std::endl;
#endif
    ++numCouldRun_;


    if (!canHeuristicRun())
        return 0;

#ifdef JJF_ZERO

    if (!when() || (when() % 10 == 1 && model_->phase() != 1) ||
            (when() % 10 == 2 && (model_->phase() != 2 && model_->phase() != 3)))
        return 0;
#endif

    int numberColumns = model_->solver()->getNumCols();
    double * newSolution = new double [numberColumns];
    int numberCuts=0;
    int numberNodes=-1;
    CbcSubProblem ** nodes=NULL;
    int returnCode=solution(solutionValue,numberNodes,numberCuts,
			    NULL,nodes,
			    newSolution);
  if (returnCode==1)
    memcpy(betterSolution, newSolution, numberColumns*sizeof(double));

    delete [] newSolution;
    return returnCode;
}
