new_kspace(int narg, char **arg, const char *suffix, int &sflag)
{
  if (suffix && lmp->suffix_enable) {
    sflag = 1;
    char estyle[256];
    sprintf(estyle,"%s/%s",arg[0],suffix);

    if (0) return NULL;

#define KSPACE_CLASS
#define KSpaceStyle(key,Class) \
  else if (strcmp(estyle,#key) == 0) return new Class(lmp,narg-1,&arg[1]);
#include "style_kspace.h"
#undef KSpaceStyle
#undef KSPACE_CLASS

  }

  sflag = 0;

  if (strcmp(arg[0],"none") == 0) return NULL;

#define KSPACE_CLASS
#define KSpaceStyle(key,Class) \
  else if (strcmp(arg[0],#key) == 0) return  new Class(lmp,narg-1,&arg[1]);
#include "style_kspace.h"
#undef KSPACE_CLASS

  else error->all(FLERR,"Invalid kspace style");
  return NULL;
}
