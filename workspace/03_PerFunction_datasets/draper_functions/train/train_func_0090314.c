GetLastLBA(void) const {
   if (lengthLBA > 0)
      return (uint64_t) firstLBA + (uint64_t) lengthLBA - UINT64_C(1);
   else
      return 0;
}
