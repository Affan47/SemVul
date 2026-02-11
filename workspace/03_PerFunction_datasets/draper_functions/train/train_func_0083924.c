InsertRepresentationChangeForUse(HValue* value,
                                              HValue* use,
                                              Representation to,
                                              bool is_truncating) {


  HInstruction* next = NULL;
  if (use->IsPhi()) {
    int index = 0;
    while (use->OperandAt(index) != value) ++index;
    next = use->block()->predecessors()->at(index)->end();
  } else {
    next = HInstruction::cast(use);
  }


  HInstruction* new_value = NULL;
  if (value->IsConstant()) {
    HConstant* constant = HConstant::cast(value);

    new_value = is_truncating
        ? constant->CopyToTruncatedInt32()
        : constant->CopyToRepresentation(to);
  }

  if (new_value == NULL) {
    new_value = new HChange(value, value->representation(), to);
  }

  new_value->InsertBefore(next);
  value->ReplaceFirstAtUse(use, new_value, to);
}
