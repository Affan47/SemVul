CanCover(LifetimePosition position) const {
  if (IsEmpty()) return false;
  return Start().Value() <= position.Value() &&
         position.Value() < End().Value();
}
