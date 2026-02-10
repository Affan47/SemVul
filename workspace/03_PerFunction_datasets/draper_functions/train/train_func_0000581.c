setNonInheritedC(const Identifier *ident, ELObj *obj,
				      const Location &loc, Interpreter &interp)
{
  radical_ = obj->asSosofo();
  if (!radical_ || !radical_->isCharacter()) {
    interp.setNextLocation(loc);
    interp.message(InterpreterMessages::invalidCharacteristicValue,
		   StringMessageArg(ident->name()));
  }
}
