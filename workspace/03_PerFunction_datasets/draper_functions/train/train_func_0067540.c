PrintAttribute(unsigned Tag, unsigned Value,
                                        StringRef ValueDesc) {
  StringRef TagName = ARMBuildAttrs::AttrTypeAsString(Tag, false);

  DictScope AS(SW, "Attribute");
  SW.printNumber("Tag", Tag);
  SW.printNumber("Value", Value);
  if (!TagName.empty())
    SW.printString("TagName", TagName);
  if (!ValueDesc.empty())
    SW.printString("Description", ValueDesc);
}
