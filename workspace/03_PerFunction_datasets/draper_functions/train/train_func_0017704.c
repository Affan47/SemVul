extract(const char *str, int &dim)
{
  dim = 2;
  if (strcmp(str,"epsilon") == 0) return (void *) epsilon;
  if (strcmp(str,"sigma") == 0) return (void *) sigma;
  if (strcmp(str,"lj_type") == 0) return (void *) lj_type;
  if (strcmp(str,"lj1") == 0) return (void *) lj1;
  if (strcmp(str,"lj2") == 0) return (void *) lj2;
  if (strcmp(str,"lj3") == 0) return (void *) lj3;
  if (strcmp(str,"lj4") == 0) return (void *) lj4;
  if (strcmp(str,"rminsq") == 0) return (void *) rminsq;
  if (strcmp(str,"emin") == 0) return (void *) emin;

  dim = 0;
  if (strcmp(str,"cut_coul") == 0) return (void *) &cut_coul;
  return NULL;
}
