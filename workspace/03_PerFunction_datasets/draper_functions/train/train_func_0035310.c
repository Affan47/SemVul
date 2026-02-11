AddDependantsToWorklist(HValue* current) {
  for (int i = 0; i < current->uses()->length(); ++i) {
    AddToWorklist(current->uses()->at(i));
  }
  for (int i = 0; i < current->OperandCount(); ++i) {
    AddToWorklist(current->OperandAt(i));
  }
}
