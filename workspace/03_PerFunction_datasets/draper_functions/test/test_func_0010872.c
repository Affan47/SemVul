splitFlags(unsigned Flags,
                            SmallVectorImpl<unsigned> &SplitFlags) {


  if (unsigned A = Flags & FlagAccessibility) {
    if (A == FlagPrivate)
      SplitFlags.push_back(FlagPrivate);
    else if (A == FlagProtected)
      SplitFlags.push_back(FlagProtected);
    else
      SplitFlags.push_back(FlagPublic);
    Flags &= ~A;
  }

#define HANDLE_DI_FLAG(ID, NAME)                                               \
  if (unsigned Bit = Flags & ID) {                                             \
    SplitFlags.push_back(Bit);                                                 \
    Flags &= ~Bit;                                                             \
  }
#include "llvm/IR/DebugInfoFlags.def"

  return Flags;
}
