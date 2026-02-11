exitNow(double bestObjective) const
{
    if ((switches_&2048) != 0) {

        switches_ &= ~2048;
        if ((switches_&1024) != 0)
            return true;
    } else if ((switches_&1) == 0) {
        return false;
    }

    OsiSolverInterface * solver = model_->solver();
    double bestPossibleObjective = solver->getObjValue() * solver->getObjSense();
    double absGap = CoinMax(model_->getAllowableGap(),
                            model_->getHeuristicGap());
    double fracGap = CoinMax(model_->getAllowableFractionGap(),
                             model_->getHeuristicFractionGap());
    double testGap = CoinMax(absGap, fracGap *
                             CoinMax(fabs(bestObjective),
                                     fabs(bestPossibleObjective)));

    if (bestObjective - bestPossibleObjective < testGap
            && model_->getCutoffIncrement() >= 0.0) {
        return true;
    } else {
        return false;
    }
}
