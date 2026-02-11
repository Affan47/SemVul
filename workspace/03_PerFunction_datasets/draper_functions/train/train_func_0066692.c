preprocess_special_segments(int *vsyscall_exists)
{
  Area area;
  int mapsfd = mtcp_sys_open2 ("/proc/self/maps", O_RDONLY);
  if (mapsfd < 0) {
    MTCP_PRINTF("error opening /proc/self/maps: %s\n",
                strerror(mtcp_sys_errno));
    mtcp_abort ();
  }

  while (mtcp_readmapsline (mapsfd, &area)) {
    if (0 == strcmp(area.name, "[vsyscall]")) {


      *vsyscall_exists = 1;
    } else if (!saved_heap_start && strcmp(area.name, "[heap]") == 0) {

      saved_heap_start = area.addr;
    } else if (strcmp(area.name, "[stack]") == 0) {


      int ret = mprotect(area.addr + area.size, 0x1000,
                         PROT_READ | PROT_WRITE | PROT_EXEC);
      if (ret == 0) {
        MTCP_PRINTF("bottom-most page of stack (page with highest address)\n"
                    "  was invisible in /proc/self/maps.\n"
                    "  It is made visible again now.\n");
      }
    }
  }
  close(mapsfd);
}
