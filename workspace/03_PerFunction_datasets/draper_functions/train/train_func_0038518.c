Modify(const char* in, size_t inlen,
                        const PerExpandData*,
                        ExpandEmitter* out, const string& arg) const {
  while (inlen > 0) {
    const char* nl = (const char*)memchr(in, '\n', inlen);
    const char* cr = (const char*)memchr(in, '\r', nl ? nl - in : inlen);
    size_t linelen;
    if (nl == NULL && cr == NULL) {

      out->Emit(in, inlen);
      break;
    } else {


      if ((nl == NULL) != (cr == NULL))
        linelen = (nl ? nl : cr) + 1 - in;
      else if (nl == cr + 1 || nl < cr)
        linelen = nl + 1 - in;
      else
        linelen = cr + 1 - in;
    }
    out->Emit(in, linelen);
    out->Emit(arg);
    in += linelen;
    inlen -= linelen;
    assert(inlen >= 0);
  }
}
