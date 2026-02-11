match (char *s, char *p, struct Capture *cap) {
  init:
  switch (*p) {
    case '(':
      return start_capt(s, p, cap);
    case ')':
      return end_capt(s, p, cap);
    case ESC:
      if (isdigit((unsigned char)(*(p+1)))) {
        s = match_capture(s, *(p+1), cap);
        if (s == NULL) return NULL;
        p+=2; goto init;
      }
      else if (*(p+1) == 'b') {
        s = matchbalance(s, p+2, cap);
        if (s == NULL) return NULL;
        p+=4; goto init;
      }
      else goto dflt;
    case '\0':
      return s;
    case '$':
      if (*(p+1) == '\0')
        return (s == cap->src_end) ? s : NULL;
      else goto dflt;
    default: dflt: {
      char *ep = luaI_classend(p);
      int m = s<cap->src_end && luaI_singlematch((unsigned char)*s, p, ep);
      switch (*ep) {
        case '?': {
          char *res;
          if (m && ((res=match(s+1, ep+1, cap)) != NULL))
            return res;
          p=ep+1; goto init;
        }
        case '*':
          return max_expand(s, p, ep, cap);
        case '+':
          return (m ? max_expand(s+1, p, ep, cap) : NULL);
        case '-':
          return min_expand(s, p, ep, cap);
        default:
          if (!m) return NULL;
          s++; p=ep; goto init;
      }
    }
  }
}
