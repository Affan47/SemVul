setNonInheritedC(const Identifier *ident, ELObj *obj,
				   const Location &loc, Interpreter &interp)
{
  AddressObj *address = obj->asAddress();
  if (!address) {
    if (obj != interp.makeFalse()) {
      interp.setNextLocation(loc);
      interp.message(InterpreterMessages::invalidCharacteristicValue,
                     StringMessageArg(ident->name()));
    }
    else
      address = interp.makeAddressNone();
  }
  addressObj_ = address;
}
