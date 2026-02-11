argError(Interpreter &interp,
			      const Location &loc,
			      const MessageType3 &msg,
			      unsigned index,
			      ELObj *obj) const
{
  NodeListObj *nl = obj->asNodeList();
  if (!nl || !nl->suppressError()) {
    interp.setNextLocation(loc);
    interp.message(msg,
		   StringMessageArg(ident_->name()),
		   OrdinalMessageArg(index + 1),
		   ELObjMessageArg(obj, interp));
  }
  return interp.makeError();
}
