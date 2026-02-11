WriteAsOperand(raw_ostream &Out, const Value *V,
                          bool PrintType, const Module *Context) {


  if (!PrintType &&
      ((!isa<Constant>(V) && !isa<MDNode>(V)) ||
       V->hasName() || isa<GlobalValue>(V))) {
    WriteAsOperandInternal(Out, V, 0, 0, Context);
    return;
  }

  if (Context == 0) Context = getModuleFromVal(V);

  TypePrinting TypePrinter;
  std::vector<const Type*> NumberedTypes;
  AddModuleTypesToPrinter(TypePrinter, NumberedTypes, Context);
  if (PrintType) {
    TypePrinter.print(V->getType(), Out);
    Out << ' ';
  }

  WriteAsOperandInternal(Out, V, &TypePrinter, 0, Context);
}
