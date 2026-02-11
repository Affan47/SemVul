objectiveValue(const ClpSimplex * model, const double * solution) const
{
     const double * cost = objective_;
     if (model && model->costRegion())
          cost = model->costRegion();
     double currentObj = 0.0;
     for (int iColumn = 0; iColumn < numberColumns_; iColumn++) {
          currentObj += cost[iColumn] * solution[iColumn];
     }
     return currentObj;
}
