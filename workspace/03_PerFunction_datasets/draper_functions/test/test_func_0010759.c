installInitialValue(Identifier *ident, Owner<Expression> &expr)
{
  for (size_t i = 0; i < initialValueNames_.size(); i++) {
    if (ident == initialValueNames_[i]) {
      if (i >= currentPartFirstInitialValue_) {
	setNextLocation(expr->location());
	message(InterpreterMessages::duplicateInitialValue,
	        StringMessageArg(ident->name()),
		initialValueValues_[i]->location());
      }
      return;
    }
  }
  initialValueValues_.resize(initialValueValues_.size() + 1);
  expr.swap(initialValueValues_.back());
  initialValueNames_.push_back(ident);
}
