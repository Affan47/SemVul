cloneArrayIfNeeded(int32_t newCapacity,
                                  int32_t growCapacity,
                                  UBool doCopyArray,
                                  int32_t **pBufferToDelete,
                                  UBool forceClone) {


  if(newCapacity == -1) {
    newCapacity = getCapacity();
  }


  if(!isWritable()) {
    return FALSE;
  }


  if(forceClone ||
     fFlags & kBufferIsReadonly ||
     fFlags & kRefCounted && refCount() > 1 ||
     newCapacity > getCapacity()
  ) {

    if(growCapacity == -1) {
      growCapacity = newCapacity;
    } else if(newCapacity <= US_STACKBUF_SIZE && growCapacity > US_STACKBUF_SIZE) {
      growCapacity = US_STACKBUF_SIZE;
    }


    UChar oldStackBuffer[US_STACKBUF_SIZE];
    UChar *oldArray;
    uint8_t flags = fFlags;

    if(flags&kUsingStackBuffer) {
      if(doCopyArray && growCapacity > US_STACKBUF_SIZE) {


        us_arrayCopy(fUnion.fStackBuffer, 0, oldStackBuffer, 0, fShortLength);
        oldArray = oldStackBuffer;
      } else {
        oldArray = 0;
      }
    } else {
      oldArray = fUnion.fFields.fArray;
    }


    if(allocate(growCapacity) ||
       newCapacity < growCapacity && allocate(newCapacity)
    ) {
      if(doCopyArray && oldArray != 0) {


        int32_t minLength = length();
        newCapacity = getCapacity();
        if(newCapacity < minLength) {
          minLength = newCapacity;
          setLength(minLength);
        }
        us_arrayCopy(oldArray, 0, getArrayStart(), 0, minLength);
      } else {
        fShortLength = 0;
      }


      if(flags & kRefCounted) {

        int32_t *pRefCount = ((int32_t *)oldArray - 1);
        if(umtx_atomic_dec(pRefCount) == 0) {
          if(pBufferToDelete == 0) {
            uprv_free(pRefCount);
          } else {

            *pBufferToDelete = pRefCount;
          }
        }
      }
    } else {


      if(!(flags&kUsingStackBuffer)) {
        fUnion.fFields.fArray = oldArray;
      }
      fFlags = flags;
      setToBogus();
      return FALSE;
    }
  }
  return TRUE;
}
