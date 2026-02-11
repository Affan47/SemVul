fromUTF32(const UChar32 *utf32, int32_t length) {
  UnicodeString result;
  int32_t capacity;


  if(length <= US_STACKBUF_SIZE) {
    capacity = US_STACKBUF_SIZE;
  } else {
    capacity = length + (length >> 4) + 4;
  }
  do {
    UChar *utf16 = result.getBuffer(capacity);
    int32_t length16;
    UErrorCode errorCode = U_ZERO_ERROR;
    u_strFromUTF32WithSub(utf16, result.getCapacity(), &length16,
        utf32, length,
        0xfffd,
        NULL,
        &errorCode);
    result.releaseBuffer(length16);
    if(errorCode == U_BUFFER_OVERFLOW_ERROR) {
      capacity = length16 + 1;
      continue;
    } else if(U_FAILURE(errorCode)) {
      result.setToBogus();
    }
    break;
  } while(TRUE);
  return result;
}
