Define(LifetimePosition position,
                        LOperand* operand,
                        LOperand* hint) {
  LiveRange* range = LiveRangeFor(operand);
  if (range == NULL) return;

  if (range->IsEmpty() || range->Start().Value() > position.Value()) {

    range->AddUseInterval(position, position.NextInstruction());
    range->AddUsePosition(position.NextInstruction(), NULL);
  } else {
    range->ShortenTo(position);
  }

  if (operand->IsUnallocated()) {
    LUnallocated* unalloc_operand = LUnallocated::cast(operand);
    range->AddUsePosition(position, unalloc_operand)->set_hint(hint);
  }
}
