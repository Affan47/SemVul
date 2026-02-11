operator=( const CbcHeuristicVND & rhs)
{
    if (this != &rhs) {
        CbcHeuristic::operator=(rhs);
        numberSolutions_ = rhs.numberSolutions_;
        howOften_ = rhs.howOften_;
        numberSuccesses_ = rhs.numberSuccesses_;
        numberTries_ = rhs.numberTries_;
        lastNode_ = rhs.lastNode_;
        delete [] baseSolution_;
        if (model_ && rhs.baseSolution_) {
            int numberColumns = model_->solver()->getNumCols();
            baseSolution_ = new double [numberColumns];
            memcpy(baseSolution_, rhs.baseSolution_, numberColumns*sizeof(double));
        } else {
            baseSolution_ = NULL;
        }
        stepSize_ = rhs.stepSize_;
        k_ = rhs.k_;
        kmax_ = rhs.kmax_;
        nDifferent_ = rhs.nDifferent_;
    }
    return *this;
}
