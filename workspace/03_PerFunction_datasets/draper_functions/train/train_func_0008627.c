Ppmd7_Alloc(CPpmd7 *p, UInt32 size, ISzAlloc *alloc)
{
  if (p->Base == 0 || p->Size != size)
  {


    if (size < UNIT_SIZE) {
      return False;
    }
    Ppmd7_Free(p, alloc);
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)alloc->Alloc(alloc, p->AlignOffset + size
        #ifndef PPMD_32BIT
        + UNIT_SIZE
        #endif
        )) == 0)
      return False;
    p->Size = size;
  }
  return True;
}
