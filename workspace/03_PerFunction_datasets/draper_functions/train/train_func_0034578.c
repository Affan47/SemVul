getAttributeGroupSlot(AttributeSet AS) {

  initialize();


  as_iterator AI = asMap.find(AS);
  return AI == asMap.end() ? -1 : (int)AI->second;
}
