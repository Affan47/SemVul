processInner(ProcessContext &context) {
    context.startTablePart();
    FOTBuilder &fotb = context.currentFOTBuilder();
    Vector<FOTBuilder *> fotbs(2);
    fotb.startTablePart(*nic_, fotbs[0], fotbs[1]);
    Vector<SymbolObj *> labels(2);
    labels[0] = context.vm().interp->portName(Interpreter::portHeader);
    labels[1] = context.vm().interp->portName(Interpreter::portFooter);
    context.pushPorts(1, labels, fotbs);
    CompoundFlowObj::processInner(context);
    context.popPorts();
    if (context.inTableRow())
      context.endTableRow();
    context.endTablePart();
    fotb.endTablePart();
  }
