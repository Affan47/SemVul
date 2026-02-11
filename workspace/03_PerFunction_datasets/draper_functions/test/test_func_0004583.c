AllocRefs(UInt32 num, ISzAlloc *alloc)
{
  size_t sizeInBytes = (size_t)num * sizeof(CLzRef);
  if (sizeInBytes / sizeof(CLzRef) != num)
    return 0;
  return (CLzRef *)alloc->Alloc(alloc, sizeInBytes);
}
