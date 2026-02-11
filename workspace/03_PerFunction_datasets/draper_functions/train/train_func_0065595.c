gradeDown(void) const
{
  if (MSView::model()!=0) return ((MSFloatVector *)_model)->gradeDown();
  else return MSIndexVector::nullVector();
}
