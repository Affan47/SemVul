processInner(ProcessContext &context) {
    context.startTable();
    FOTBuilder &fotb = context.currentFOTBuilder();
    fotb.startTable(*nic_);
    Interpreter &interp = *context.vm().interp;
    Vector<size_t> dep;
    ELObj *obj = context.currentStyleStack().actual(interp.tableBorderC(), interp, dep);
    StyleObj *borderStyle;
    if (obj == interp.makeFalse())
      borderStyle = interp.borderFalseStyle();
    else if (obj == interp.makeTrue())
      borderStyle = interp.borderTrueStyle();
    else {
      SosofoObj *sosofo = obj->asSosofo();
      if (!sosofo || !sosofo->tableBorderStyle(borderStyle))
	borderStyle = 0;
    }
    border(nic_->beforeRowBorder, borderStyle, &FOTBuilder::tableBeforeRowBorder, context);
    border(nic_->afterRowBorder, borderStyle, &FOTBuilder::tableAfterRowBorder, context);
    border(nic_->beforeColumnBorder, borderStyle, &FOTBuilder::tableBeforeColumnBorder, context);
    border(nic_->afterColumnBorder, borderStyle, &FOTBuilder::tableAfterColumnBorder, context);
    CompoundFlowObj::processInner(context);
    if (context.inTableRow())
      context.endTableRow();
    context.endTable();
    fotb.endTable();
  }
