setNonInheritedC(const Identifier *ident, ELObj *obj,
  			const Location &loc, Interpreter &interp) {
    Identifier::SyntacticKey key;
    if (ident->syntacticKey(key)) {
      switch (key) {
      case Identifier::keyIsStartsRow:
        interp.convertBooleanC(obj, ident, loc, nic_->startsRow);
	return;
      case Identifier::keyIsEndsRow:
        interp.convertBooleanC(obj, ident, loc, nic_->endsRow);
	return;
      case Identifier::keyColumnNumber:
      case Identifier::keyNColumnsSpanned:
      case Identifier::keyNRowsSpanned:
	{
	  long n;
          if (!interp.convertIntegerC(obj, ident, loc, n))
	    return;
          if (n <= 0) {
	    interp.setNextLocation(loc);
	    interp.message(InterpreterMessages::invalidCharacteristicValue,
  		 	   StringMessageArg(ident->name()));
	    return;
          }
	  if (key == Identifier::keyColumnNumber) {
	    nic_->columnIndex = n - 1;
	    nic_->hasColumnNumber = 1;
	  }
	  else if (key == Identifier::keyNColumnsSpanned)
	    nic_->nColumnsSpanned = n;
	  else
	    nic_->nRowsSpanned = n;
	}
	return;
      default:
	break;
      }
    }
    CANNOT_HAPPEN();
  }
