mpool_create() {
  struct MP mp, *mpool_p;
  size_t sz;
  memset(&mp, 0, sizeof(mp));
  mp.psize = cli_getpagesize();
  sz = align_to_pagesize(&mp, MIN_FRAGSIZE);
  mp.u.mpm.usize = sizeof(struct MPMAP);
  mp.u.mpm.size = sz - sizeof(mp);
  if (FRAGSBITS > 255) {
      cli_errmsg("At most 255 frags possible!\n");
      return NULL;
  }
  if (fragsz[0] < sizeof(void*)) {
      cli_errmsg("fragsz[0] too small!\n");
      return NULL;
  }
#ifndef _WIN32
  if ((mpool_p = (struct MP *)mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE|ANONYMOUS_MAP, -1, 0)) == MAP_FAILED)
#else
  if(!(mpool_p = (struct MP *)VirtualAlloc(NULL, sz, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)))
#endif
    return NULL;
#ifdef CL_DEBUG
  memset(mpool_p, ALLOCPOISON, sz);
#endif
  memcpy(mpool_p, &mp, sizeof(mp));
  spam("Map created @%p->%p - size %lu out of %lu - voidptr=%lu\n", mpool_p, (char *)mpool_p + mp.u.mpm.size, (unsigned long)mp.u.mpm.usize, (unsigned long)mp.u.mpm.size, (unsigned long)SIZEOF_VOID_P);
  return mpool_p;
}
