operator=( const CbcHeuristicProximity & rhs)
{
    if (this != &rhs) {
        CbcHeuristic::operator=(rhs);
        numberSolutions_ = rhs.numberSolutions_;
        delete [] used_;
        delete feasibilityPump_;
	feasibilityPump_ = NULL;
	if (model_ && rhs.used_) {
            int numberColumns = model_->solver()->getNumCols();
            used_ = CoinCopyOfArray(rhs.used_, numberColumns);
	    if (rhs.feasibilityPump_)
	      feasibilityPump_ = new CbcHeuristicFPump(*rhs.feasibilityPump_);
        } else {
            used_ = NULL;
        }
    }
    return *this;
}
