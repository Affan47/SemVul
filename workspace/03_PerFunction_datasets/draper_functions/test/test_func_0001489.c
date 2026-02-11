hashShallowTypeReference(dwarf::Attribute Attribute,
                                       const DIE &Entry, StringRef Name) {

  addULEB128('N');


  addULEB128(Attribute);


  if (const DIE *Parent = Entry.getParent())
    addParentContext(*Parent);


  addULEB128('E');


  addString(Name);


}
