Init() {
  if (vdso_base_ == ElfMemImage::kInvalidBase) {


    if (RunningOnValgrind()) {
      vdso_base_ = NULL;
      getcpu_fn_ = &GetCPUViaSyscall;
      return NULL;
    }
    int fd = open("/proc/self/auxv", O_RDONLY);
    if (fd == -1) {

      vdso_base_ = NULL;
      getcpu_fn_ = &GetCPUViaSyscall;
      return NULL;
    }
    ElfW(auxv_t) aux;
    while (read(fd, &aux, sizeof(aux)) == sizeof(aux)) {
      if (aux.a_type == AT_SYSINFO_EHDR) {
        COMPILE_ASSERT(sizeof(vdso_base_) == sizeof(aux.a_un.a_val),
                       unexpected_sizeof_pointer_NE_sizeof_a_val);
        vdso_base_ = reinterpret_cast<void *>(aux.a_un.a_val);
        break;
      }
    }
    close(fd);
    if (vdso_base_ == ElfMemImage::kInvalidBase) {

      vdso_base_ = NULL;
    }
  }
  GetCpuFn fn = &GetCPUViaSyscall;
  if (vdso_base_) {
    VDSOSupport vdso;
    SymbolInfo info;
    if (vdso.LookupSymbol("__vdso_getcpu", "LINUX_2.6", STT_FUNC, &info)) {


      fn = (GetCpuFn)(info.address);
    }
  }


  base::subtle::MemoryBarrier();
  getcpu_fn_ = fn;
  return vdso_base_;
}
