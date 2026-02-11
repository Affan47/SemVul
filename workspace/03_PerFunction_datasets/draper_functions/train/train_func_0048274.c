end_capture (lua_State *L, const char *s, const char *p,
                                struct Capture *cap) {
  int l = capture_to_close(L, cap);
  const char *res;
  cap->capture[l].len = s - cap->capture[l].init;
  if ((res = match(L, s, p+1, cap)) == NULL)
    cap->capture[l].len = -1;
  return res;
}
