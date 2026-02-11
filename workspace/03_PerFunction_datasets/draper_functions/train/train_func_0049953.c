branch()
{
    decrementNumberBranchesLeft();
    OsiRowCut * cut;
    if (way_ < 0) {
        cut = &down_;
        way_ = 1;
    } else {
        cut = &up_;
        way_ = -1;
    }
    printf("CUT %s ", (way_ == -1) ? "up" : "down");
    cut->print();

    double lb = cut->lb();
    double ub = cut->ub();
    int n = cut->row().getNumElements();
    const int * column = cut->row().getIndices();
    const double * element = cut->row().getElements();
    OsiSolverInterface * solver = model_->solver();
    const double * upper = solver->getColUpper();
    const double * lower = solver->getColLower();
    double low = 0.0;
    double high = 0.0;
    for (int i = 0; i < n; i++) {
        int iColumn = column[i];
        double value = element[i];
        if (value > 0.0) {
            high += upper[iColumn] * value;
            low += lower[iColumn] * value;
        } else {
            high += lower[iColumn] * value;
            low += upper[iColumn] * value;
        }
    }


    if (low + 1.0e-8 >= ub && canFix_) {

        for (int i = 0; i < n; i++) {
            int iColumn = column[i];
            double value = element[i];
            if (value > 0.0) {
                solver->setColUpper(iColumn, lower[iColumn]);
            } else {
                solver->setColLower(iColumn, upper[iColumn]);
            }
        }
    } else if (high - 1.0e-8 <= lb && canFix_) {

        for (int i = 0; i < n; i++) {
            int iColumn = column[i];
            double value = element[i];
            if (value > 0.0) {
                solver->setColLower(iColumn, upper[iColumn]);
            } else {
                solver->setColUpper(iColumn, lower[iColumn]);
            }
        }
    } else {

        model_->setNextRowCut(*cut);
    }
    return 0.0;
}
