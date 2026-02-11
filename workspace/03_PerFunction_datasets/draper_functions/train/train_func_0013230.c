AllocateStringFromAscii(Vector<const char> string,
                                           PretenureFlag pretenure) {
  if (string.length() == 1) {
    return Heap::LookupSingleCharacterStringFromCode(string[0]);
  }
  Object* result;
  { MaybeObject* maybe_result =
        AllocateRawAsciiString(string.length(), pretenure);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }


  SeqAsciiString* string_result = SeqAsciiString::cast(result);
  for (int i = 0; i < string.length(); i++) {
    string_result->SeqAsciiStringSet(i, string[i]);
  }
  return result;
}
