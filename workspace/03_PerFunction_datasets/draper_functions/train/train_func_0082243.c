print(raw_ostream &OS, bool ) const {
  TypePrinting TP;
  TP.print(const_cast<Type*>(this), OS);


  if (StructType *STy = dyn_cast<StructType>(const_cast<Type*>(this)))
    if (!STy->isLiteral()) {
      OS << " = type ";
      TP.printStructBody(STy, OS);
    }
}
