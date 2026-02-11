extract(char *name)
{
  if (strcmp(name,"mass") == 0) return (void *) mass;

  if (strcmp(name,"id") == 0) return (void *) tag;
  if (strcmp(name,"type") == 0) return (void *) type;
  if (strcmp(name,"mask") == 0) return (void *) mask;
  if (strcmp(name,"image") == 0) return (void *) image;
  if (strcmp(name,"x") == 0) return (void *) x;
  if (strcmp(name,"v") == 0) return (void *) v;
  if (strcmp(name,"f") == 0) return (void *) f;
  if (strcmp(name,"molecule") == 0) return (void *) molecule;
  if (strcmp(name,"q") == 0) return (void *) q;
  if (strcmp(name,"mu") == 0) return (void *) mu;
  if (strcmp(name,"omega") == 0) return (void *) omega;
  if (strcmp(name,"amgmom") == 0) return (void *) angmom;
  if (strcmp(name,"torque") == 0) return (void *) torque;
  if (strcmp(name,"radius") == 0) return (void *) radius;
  if (strcmp(name,"rmass") == 0) return (void *) rmass;
  if (strcmp(name,"vfrac") == 0) return (void *) vfrac;
  if (strcmp(name,"s0") == 0) return (void *) s0;

  return NULL;
}
