GetSequenceOfItems() {
    GDCM_LEGACY_REPLACED_BODY(DataElement::GetSequenceOfItems, "GDCM 2.2",
                              DataElement::GetValueAsSQ);
    SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if(!sqi)
      {

      assert( IsEmpty() );
      }
    return sqi;
  }
