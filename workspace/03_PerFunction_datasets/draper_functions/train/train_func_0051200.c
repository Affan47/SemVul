operator new(size_t N, const NamedBufferAlloc &Alloc) {
  SmallString<256> NameBuf;
  StringRef NameRef = Alloc.Name.toStringRef(NameBuf);

  char *Mem = static_cast<char *>(operator new(N + NameRef.size() + 1));
  CopyStringRef(Mem + N, NameRef);
  return Mem;
}
