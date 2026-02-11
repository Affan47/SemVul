processType(DIType DT) {
  if (!addType(DT))
    return;
  if (DT.getVersion() <= LLVMDebugVersion10)
    addCompileUnit(DT.getCompileUnit());
  if (DT.isCompositeType()) {
    DICompositeType DCT(DT);
    processType(DCT.getTypeDerivedFrom());
    DIArray DA = DCT.getTypeArray();
    for (unsigned i = 0, e = DA.getNumElements(); i != e; ++i) {
      DIDescriptor D = DA.getElement(i);
      if (D.isType())
        processType(DIType(D));
      else if (D.isSubprogram())
        processSubprogram(DISubprogram(D));
    }
  } else if (DT.isDerivedType()) {
    DIDerivedType DDT(DT);
    processType(DDT.getTypeDerivedFrom());
  }
}
