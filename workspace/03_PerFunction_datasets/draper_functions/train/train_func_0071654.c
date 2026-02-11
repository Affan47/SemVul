processInner(ProcessContext &context)
{
  FOTBuilder &fotb = context.currentFOTBuilder();
  Vector<FOTBuilder *> fotbs(nic_->namedModes.size());
  fotb.startMultiMode(nic_->hasPrincipalMode ? &nic_->principalMode : 0,
		      nic_->namedModes,
		      fotbs);
  Vector<SymbolObj *> portSyms(nic_->namedModes.size());
  for (size_t i = 0; i < portSyms.size(); i++)
    portSyms[i] = context.vm().interp->makeSymbol(nic_->namedModes[i].name);
  context.pushPorts(nic_->hasPrincipalMode, portSyms, fotbs);
  CompoundFlowObj::processInner(context);
  context.popPorts();
  fotb.endMultiMode();
}
