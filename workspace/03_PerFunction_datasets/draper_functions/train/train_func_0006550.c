computeInternalObjectiveValue()
{
     int iSequence;

     double objectiveValue = 0.0;
     const double * obj = objective();
     if (!columnScale_) {
          for (iSequence = 0; iSequence < numberColumns_; iSequence++) {
               double value = solution_[iSequence];
               objectiveValue += value * obj[iSequence];
          }
     } else {
          for (iSequence = 0; iSequence < numberColumns_; iSequence++) {
               double value = solution_[iSequence] * columnScale_[iSequence];
               objectiveValue += value * obj[iSequence];
          }
     }
     objectiveValue *= optimizationDirection_ / rhsScale_;
     objectiveValue -= dblParam_[ClpObjOffset];
     return objectiveValue;
}
