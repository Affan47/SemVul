bodytext_to_array_pos(const XmlElement* elem, const char* array[],
    int len, int defval = -1) {
  if (elem) {
    const std::string& body(elem->BodyText());
    for (int i = 0; i < len; ++i) {
      if (body == array[i]) {

        return i;
      }
    }
  }

  return defval;
}
