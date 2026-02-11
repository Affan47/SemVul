CalculateOffsets() {
  int element_count = elements()->length();


  int cp_offset = 0;
  for (int i = 0; i < element_count; i++) {
    TextElement& elm = elements()->at(i);
    elm.cp_offset = cp_offset;
    if (elm.type == TextElement::ATOM) {
      cp_offset += elm.data.u_atom->data().length();
    } else {
      cp_offset++;
      Vector<const uc16> quarks = elm.data.u_atom->data();
    }
  }
}
