AllocateSubString(String* buffer,
                                int start,
                                int end,
                                PretenureFlag pretenure) {
  int length = end - start;

  if (length == 1) {
    return Heap::LookupSingleCharacterStringFromCode(
        buffer->Get(start));
  } else if (length == 2) {


    unsigned c1 = buffer->Get(start);
    unsigned c2 = buffer->Get(start + 1);
    return MakeOrFindTwoCharacterString(c1, c2);
  }


  buffer = buffer->TryFlattenGetString();

  Object* result;
  { MaybeObject* maybe_result = buffer->IsAsciiRepresentation()
                   ? AllocateRawAsciiString(length, pretenure )
                   : AllocateRawTwoByteString(length, pretenure);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }
  String* string_result = String::cast(result);

  if (buffer->IsAsciiRepresentation()) {
    ASSERT(string_result->IsAsciiRepresentation());
    char* dest = SeqAsciiString::cast(string_result)->GetChars();
    String::WriteToFlat(buffer, dest, start, end);
  } else {
    ASSERT(string_result->IsTwoByteRepresentation());
    uc16* dest = SeqTwoByteString::cast(string_result)->GetChars();
    String::WriteToFlat(buffer, dest, start, end);
  }

  return result;
}
