CaseInsensitiveCompareUC16(
    Address byte_offset1,
    Address byte_offset2,
    size_t byte_length,
    Isolate* isolate) {
  ASSERT(isolate == Isolate::Current());
  unibrow::Mapping<unibrow::Ecma262Canonicalize>* canonicalize =
      isolate->regexp_macro_assembler_canonicalize();


  ASSERT(byte_length % 2 == 0);
  uc16* substring1 = reinterpret_cast<uc16*>(byte_offset1);
  uc16* substring2 = reinterpret_cast<uc16*>(byte_offset2);
  size_t length = byte_length >> 1;

  for (size_t i = 0; i < length; i++) {
    unibrow::uchar c1 = substring1[i];
    unibrow::uchar c2 = substring2[i];
    if (c1 != c2) {
      unibrow::uchar s1[1] = { c1 };
      canonicalize->get(c1, '\0', s1);
      if (s1[0] != c2) {
        unibrow::uchar s2[1] = { c2 };
        canonicalize->get(c2, '\0', s2);
        if (s1[0] != s2[0]) {
          return 0;
        }
      }
    }
  }
  return 1;
}
