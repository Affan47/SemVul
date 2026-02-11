getConsecutiveDirection() const {
  if (StepValue && (StepValue->isOne() || StepValue->isMinusOne()))
    return StepValue->getSExtValue();
  return 0;
}
