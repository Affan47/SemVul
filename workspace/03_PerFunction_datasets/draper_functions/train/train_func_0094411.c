setNonInheritedC(const Identifier *ident,
						 ELObj *obj,
						 const Location &loc,
						 Interpreter &interp)
{
  SosofoObj *sosofo = obj->asSosofo();
  if (!sosofo) {
    interp.setNextLocation(loc);
    interp.message(InterpreterMessages::invalidCharacteristicValue,
		   StringMessageArg(ident->name()));
    return;
  }
  Identifier::SyntacticKey key;
  if (ident->syntacticKey(key)) {
    switch (key) {
    case Identifier::keyLeftHeader:
      hf_->part[(FOTBuilder::leftHF | FOTBuilder::headerHF) >> nPageTypeBits] = sosofo;
      return;
    case Identifier::keyCenterHeader:
      hf_->part[(FOTBuilder::centerHF | FOTBuilder::headerHF) >> nPageTypeBits] = sosofo;
      return;
    case Identifier::keyRightHeader:
      hf_->part[(FOTBuilder::rightHF | FOTBuilder::headerHF) >> nPageTypeBits] = sosofo;
      return;
    case Identifier::keyLeftFooter:
      hf_->part[(FOTBuilder::leftHF | FOTBuilder::footerHF) >> nPageTypeBits] = sosofo;
      return;
    case Identifier::keyCenterFooter:
      hf_->part[(FOTBuilder::centerHF | FOTBuilder::footerHF) >> nPageTypeBits] = sosofo;
      return;
    case Identifier::keyRightFooter:
      hf_->part[(FOTBuilder::rightHF | FOTBuilder::footerHF) >> nPageTypeBits] = sosofo;
      return;
    default:
      break;
    }
  }
  CANNOT_HAPPEN();
}
