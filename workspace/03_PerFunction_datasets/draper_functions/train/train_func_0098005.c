clampStackAlignment(bool ShouldClamp, unsigned Align,
                                           unsigned StackAlign) {
  if (!ShouldClamp || Align <= StackAlign)
    return Align;
  DEBUG(dbgs() << "Warning: requested alignment " << Align
               << " exceeds the stack alignment " << StackAlign
               << " when stack realignment is off" << '\n');
  return StackAlign;
}
