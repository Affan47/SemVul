usefulInformation() const
{
    OsiBranchingInformation usefulInfo(solver_, normalSolver(), false);

    usefulInfo.solution_ = testSolution_;
    usefulInfo.integerTolerance_ = dblParam_[CbcIntegerTolerance] ;
    usefulInfo.hotstartSolution_ = hotstartSolution_;
    usefulInfo.numberSolutions_ = numberSolutions_;
    usefulInfo.numberBranchingSolutions_ = numberSolutions_ - numberHeuristicSolutions_;
    usefulInfo.depth_ = -1;
    return usefulInfo;
}
