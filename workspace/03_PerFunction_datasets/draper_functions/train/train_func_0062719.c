my_stricmp(const char *s1, const char *s2) {
  for ( ; *s1 && *s2 && (toupper((unsigned char)*s1) ==
			 toupper((unsigned char)*s2)); ++s1, ++s2)
    ;
  return toupper((unsigned char) *s1) - toupper((unsigned char) *s2);
}
