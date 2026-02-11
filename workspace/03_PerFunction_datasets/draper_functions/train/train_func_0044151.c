print(raw_ostream &O) const {
  switch (Ty) {
  case isNone:
    llvm_unreachable("Expected valid DIEValue");
#define HANDLE_DIEVALUE(T)                                                     \
  case is##T:                                                                  \
    getDIE##T().print(O);                                                      \
    break;
#include "llvm/CodeGen/DIEValue.def"
  }
}
