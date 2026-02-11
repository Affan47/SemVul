allocate(int32_t capacity) {
  if(capacity <= US_STACKBUF_SIZE) {
    fFlags = kShortString;
  } else {


    int32_t words = (int32_t)(((sizeof(int32_t) + (capacity + 1) * U_SIZEOF_UCHAR + 15) & ~15) >> 2);
    int32_t *array = (int32_t*) uprv_malloc( sizeof(int32_t) * words );
    if(array != 0) {

      *array++ = 1;


      fUnion.fFields.fArray = (UChar *)array;
      fUnion.fFields.fCapacity = (int32_t)((words - 1) * (sizeof(int32_t) / U_SIZEOF_UCHAR));
      fFlags = kLongString;
    } else {
      fShortLength = 0;
      fUnion.fFields.fArray = 0;
      fUnion.fFields.fCapacity = 0;
      fFlags = kIsBogus;
      return FALSE;
    }
  }
  return TRUE;
}
