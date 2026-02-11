initMessage(Message &msg)
{
  mgr_->initMessage(msg);
  if (valid_) {
    StringC rniPcdata = metaSyntax_->delimGeneral(Syntax::dRNI);
    rniPcdata += metaSyntax_->reservedName(Syntax::rPCDATA);
    getOpenElementInfo(msg.openElementInfo, rniPcdata);
  }
}
