is_tjp_object (const char *candidate) {
  return strcmp (candidate, "tjp") == 0 ||
    strcmp (candidate, "thisJoinPoint") == 0;
}
