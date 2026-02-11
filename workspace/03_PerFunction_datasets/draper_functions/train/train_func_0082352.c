ClearOperands() {
  for (int i = 0; i < OperandCount(); ++i) {
    SetOperandAt(i, NULL);
  }
}
