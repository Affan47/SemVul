getAttributeValueAsString(
    const DWARFCompileUnit* cu,
    const uint16_t attr,
    const char* fail_value) const {
  DWARFFormValue form_value;
  if (getAttributeValue(cu, attr, form_value)) {
    DataExtractor stringExtractor(cu->getContext().getStringSection(),
        false, 0);
    return form_value.getAsCString(&stringExtractor);
  }
  return fail_value;
}
