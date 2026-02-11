edit_distance(llvm::StringRef Other,
                                  bool AllowReplacements) {


  size_type m = size();
  size_type n = Other.size();

  const unsigned SmallBufferSize = 64;
  unsigned SmallBuffer[SmallBufferSize];
  unsigned *Allocated = 0;
  unsigned *previous = SmallBuffer;
  if (2*(n + 1) > SmallBufferSize)
    Allocated = previous = new unsigned [2*(n+1)];
  unsigned *current = previous + (n + 1);

  for (unsigned i = 0; i <= n; ++i)
    previous[i] = i;

  for (size_type y = 1; y <= m; ++y) {
    current[0] = y;
    for (size_type x = 1; x <= n; ++x) {
      if (AllowReplacements) {
        current[x] = min(previous[x-1] + ((*this)[y-1] == Other[x-1]? 0u:1u),
                         min(current[x-1], previous[x])+1);
      }
      else {
        if ((*this)[y-1] == Other[x-1]) current[x] = previous[x-1];
        else current[x] = min(current[x-1], previous[x]) + 1;
      }
    }

    unsigned *tmp = current;
    current = previous;
    previous = tmp;
  }

  unsigned Result = previous[n];
  delete [] Allocated;

  return Result;
}
