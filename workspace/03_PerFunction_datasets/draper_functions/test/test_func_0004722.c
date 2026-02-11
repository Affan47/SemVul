incrementUsed(const double * solution)
{

    int numberColumns = solver_->getNumCols();
    for (int i = 0; i < numberColumns; i++) {
        if (solution[i])
            usedInSolution_[i]++;
    }
}
