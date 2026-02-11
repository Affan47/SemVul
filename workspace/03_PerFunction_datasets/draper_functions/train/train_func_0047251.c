downEstimate() const
{
    const double * solution = model_->testSolution();
    const double * lower = model_->getCbcColLower();
    const double * upper = model_->getCbcColUpper();
    double value = solution[columnNumber_];
    value = CoinMax(value, lower[columnNumber_]);
    value = CoinMin(value, upper[columnNumber_]);
    if (upper[columnNumber_] == lower[columnNumber_]) {

        return 0.0;
    }
    double integerTolerance =
        model_->getDblParam(CbcModel::CbcIntegerTolerance);
    double below = floor(value + integerTolerance);
    double above = below + 1.0;
    if (above > upper[columnNumber_]) {
        above = below;
        below = above - 1;
    }
    double downCost = CoinMax((value - below) * downDynamicPseudoCost_, 0.0);
    return downCost;
}
