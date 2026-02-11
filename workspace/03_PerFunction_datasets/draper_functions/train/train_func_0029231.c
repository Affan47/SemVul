ReadBlockIntoBuffer(String* input,
                                 ReadBlockBuffer* rbb,
                                 unsigned* offset_ptr,
                                 unsigned max_chars) {
  ASSERT(*offset_ptr <= (unsigned)input->length());
  if (max_chars == 0) return;

  switch (StringShape(input).representation_tag()) {
    case kSeqStringTag:
      if (input->IsAsciiRepresentation()) {
        SeqAsciiString::cast(input)->SeqAsciiStringReadBlockIntoBuffer(rbb,
                                                                 offset_ptr,
                                                                 max_chars);
        return;
      } else {
        SeqTwoByteString::cast(input)->SeqTwoByteStringReadBlockIntoBuffer(rbb,
                                                                     offset_ptr,
                                                                     max_chars);
        return;
      }
    case kConsStringTag:
      ConsString::cast(input)->ConsStringReadBlockIntoBuffer(rbb,
                                                             offset_ptr,
                                                             max_chars);
      return;
    case kExternalStringTag:
      if (input->IsAsciiRepresentation()) {
        ExternalAsciiString::cast(input)->
            ExternalAsciiStringReadBlockIntoBuffer(rbb, offset_ptr, max_chars);
      } else {
        ExternalTwoByteString::cast(input)->
            ExternalTwoByteStringReadBlockIntoBuffer(rbb,
                                                     offset_ptr,
                                                     max_chars);
       }
       return;
    default:
      break;
  }

  UNREACHABLE();
  return;
}
