set(const StringPiece &source, UErrorCode &status, uint32_t ) {
    if (U_FAILURE(status)) {
        return;
    }

#if 0
    if(fastpathBits==(kFastpathOk|kNoDecimal)) {
      int32_t size = source.size();
      const char *data = source.data();
      int64_t r = 0;
      int64_t m = 1;

      while(size>0) {
        char ch = data[--size];
        if(ch=='+') {
          break;
        } else if(ch=='-') {
          r = -r;
          break;
        } else {
          int64_t d = ch-'0';

          r+=(d)*m;
          m *= 10;
        }
      }

      set(r);
    } else
#endif
        {


      int32_t numDigits = source.length();
      if (numDigits > fContext.digits) {

        decNumber *t = fStorage.resize(numDigits, fStorage.getCapacity());
        if (t == NULL) {
          status = U_MEMORY_ALLOCATION_ERROR;
          return;
        }
        fDecNumber = t;
        fContext.digits = numDigits;
      }

      fContext.status = 0;
      uprv_decNumberFromString(fDecNumber, source.data(), &fContext);
      if ((fContext.status & DEC_Conversion_syntax) != 0) {
        status = U_DECIMAL_NUMBER_SYNTAX_ERROR;
      }
    }
    internalClear();
}
