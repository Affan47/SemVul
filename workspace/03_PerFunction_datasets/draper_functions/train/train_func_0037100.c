new_avec(const char *style, char *suffix, int &sflag)
{
  if (suffix && lmp->suffix_enable) {
    sflag = 1;
    char estyle[256];
    sprintf(estyle,"%s/%s",style,suffix);

    if (0) return NULL;

#define ATOM_CLASS
#define AtomStyle(key,Class) \
    else if (strcmp(estyle,#key) == 0) return new Class(lmp);
#include "style_atom.h"
#undef AtomStyle
#undef ATOM_CLASS

  }

  sflag = 0;

  if (0) return NULL;

#define ATOM_CLASS
#define AtomStyle(key,Class) \
  else if (strcmp(style,#key) == 0) return new Class(lmp);
#include "style_atom.h"
#undef ATOM_CLASS

  else error->all(FLERR,"Invalid atom style");

  return NULL;
}
