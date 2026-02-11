GetAttributeValue(
    const char* attribute_name) const {

  assert(IsValidAttribute(pragma_id_, attribute_name, strlen(attribute_name)));
  for (vector<pair<string, string> >::const_iterator it =
           names_and_values_.begin(); it != names_and_values_.end(); ++it) {
    if (strcasecmp(attribute_name, it->first.c_str()) == 0)
      return &it->second;
  }
  return NULL;
}
