install_builtin_functions (void)
{
#define DEF_BUILTIN(ENUM, NAME, CLASS, TYPE, LIBTYPE, BOTH_P, FALLBACK_P, \
		    NONANSI_P, ATTRS, IMPLICIT, COND)			\
  if (NAME && COND)							\
    def_builtin_1 (ENUM, NAME, CLASS,                                   \
                   builtin_types[(int) TYPE],                           \
                   builtin_types[(int) LIBTYPE],                        \
                   BOTH_P, FALLBACK_P, NONANSI_P,                       \
                   built_in_attributes[(int) ATTRS], IMPLICIT);
#include "builtins.def"
#undef DEF_BUILTIN
}
