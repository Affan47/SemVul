Modify(const char* in, size_t inlen,
                        const PerExpandData*,
                        ExpandEmitter* out, const string& arg) const {
  const char* pos = in;
  const char* start = pos;
  const char* const limit = in + inlen;
  while (pos < limit) {
    switch (*pos) {
      default:

        ++pos;
        continue;

      case '&':  EmitRun(start, pos, out); APPEND("&amp;");  break;
      case '"':  EmitRun(start, pos, out); APPEND("&quot;"); break;
      case '\'': EmitRun(start, pos, out); APPEND("&#39;");  break;
      case '<':  EmitRun(start, pos, out); APPEND("&lt;");   break;
      case '>':  EmitRun(start, pos, out); APPEND("&gt;");   break;

      case '\r': case '\n': case '\v': case '\f': case '\t':
        EmitRun(start, pos, out); APPEND(" ");      break;
    }
    start = ++pos;
  }
  EmitRun(start, pos, out);
}
