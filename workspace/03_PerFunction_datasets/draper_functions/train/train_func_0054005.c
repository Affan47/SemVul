legalizeCallAttributes(AttributeSet AS) {
  AttributeSet Ret;

  for (unsigned Slot = 0; Slot < AS.getNumSlots(); Slot++) {
    unsigned Index = AS.getSlotIndex(Slot);

    if (Index == AttributeSet::ReturnIndex ||
        Index == AttributeSet::FunctionIndex) {

      for (Attribute Attr : make_range(AS.begin(Slot), AS.end(Slot))) {


        if (Attr.hasAttribute(Attribute::ReadNone) ||
            Attr.hasAttribute(Attribute::ReadOnly))
          continue;


        if (Attr.hasAttribute("statepoint-num-patch-bytes") ||
            Attr.hasAttribute("statepoint-id"))
          continue;

        Ret = Ret.addAttributes(
            AS.getContext(), Index,
            AttributeSet::get(AS.getContext(), Index, AttrBuilder(Attr)));
      }
    }


  }

  return Ret;
}
