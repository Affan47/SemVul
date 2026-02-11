VerifyFunctionAttrs(const FunctionType *FT,
                                   const AttrListPtr &Attrs,
                                   const Value *V) {
  if (Attrs.isEmpty())
    return;

  bool SawNest = false;

  for (unsigned i = 0, e = Attrs.getNumSlots(); i != e; ++i) {
    const AttributeWithIndex &Attr = Attrs.getSlot(i);

    const Type *Ty;
    if (Attr.Index == 0)
      Ty = FT->getReturnType();
    else if (Attr.Index-1 < FT->getNumParams())
      Ty = FT->getParamType(Attr.Index-1);
    else
      break;

    VerifyParameterAttrs(Attr.Attrs, Ty, Attr.Index == 0, V);

    if (Attr.Attrs & Attribute::Nest) {
      Assert1(!SawNest, "More than one parameter has attribute nest!", V);
      SawNest = true;
    }

    if (Attr.Attrs & Attribute::StructRet)
      Assert1(Attr.Index == 1, "Attribute sret not on first parameter!", V);
  }

  Attributes FAttrs = Attrs.getFnAttributes();
  Attributes NotFn = FAttrs & (~Attribute::FunctionOnly);
  Assert1(!NotFn, "Attribute " + Attribute::getAsString(NotFn) +
          " does not apply to the function!", V);

  for (unsigned i = 0;
       i < array_lengthof(Attribute::MutuallyIncompatible); ++i) {
    Attributes MutI = FAttrs & Attribute::MutuallyIncompatible[i];
    Assert1(!(MutI & (MutI - 1)), "Attributes " +
            Attribute::getAsString(MutI) + " are incompatible!", V);
  }
}
