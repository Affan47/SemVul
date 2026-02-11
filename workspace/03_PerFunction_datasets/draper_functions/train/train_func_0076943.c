OsiSolverLinearizedQuadratic (
    const OsiSolverLinearizedQuadratic & rhs)
        : OsiSolverInterface(rhs)
        , OsiClpSolverInterface(rhs)
{
    bestObjectiveValue_ = rhs.bestObjectiveValue_;
    if (rhs.bestSolution_) {
        bestSolution_ = CoinCopyOfArray(rhs.bestSolution_, modelPtr_->numberColumns());
    } else {
        bestSolution_ = NULL;
    }
    specialOptions3_ = rhs.specialOptions3_;
    if (rhs.quadraticModel_) {
        quadraticModel_ = new ClpSimplex(*rhs.quadraticModel_);
    } else {
        quadraticModel_ = NULL;
    }
    checkQP(rhs.quadraticModel_);
    checkQP(quadraticModel_);
}
