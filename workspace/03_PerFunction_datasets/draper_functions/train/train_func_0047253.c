_create_tmpf(Evas_Object *obj, void *data, int size, char *format __UNUSED__)
{
#ifdef HAVE_SYS_MMAN_H
   Evas_Object_Image *o;
   char buf[PATH_MAX];
   void *dst;
   int fd = -1;

   o = (Evas_Object_Image *)(obj->object_data);
#ifdef __linux__
   snprintf(buf, sizeof(buf), "/dev/shm/.evas-tmpf-%i-%p-%i-XXXXXX",
            (int)getpid(), data, (int)size);
   fd = mkstemp(buf);
#endif
   if (fd < 0)
     {
        const char *tmpdir = getenv("TMPDIR");

        if (!tmpdir)
          {
             tmpdir = getenv("TMP");
             if (!tmpdir)
               {
                  tmpdir = getenv("TEMP");
                  if (!tmpdir) tmpdir = "/tmp";
               }
          }
        snprintf(buf, sizeof(buf), "%s/.evas-tmpf-%i-%p-%i-XXXXXX",
                 tmpdir, (int)getpid(), data, (int)size);
        fd = mkstemp(buf);
        if (fd < 0) return;
     }
   if (ftruncate(fd, size) < 0)
     {
        unlink(buf);
        close(fd);
        return;
     }
#ifdef __linux__
   unlink(buf);
#endif

   eina_mmap_safety_enabled_set(EINA_TRUE);

   dst = mmap(NULL, size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fd, 0);
   if (dst == MAP_FAILED)
     {
        close(fd);
        return;
     }
   o->tmpf_fd = fd;
#ifdef __linux__
   snprintf(buf, sizeof(buf), "/proc/%li/fd/%i", (long)getpid(), fd);
#endif
   o->tmpf = eina_stringshare_add(buf);
   memcpy(dst, data, size);
   munmap(dst, size);
#else
   (void) obj;
   (void) data;
   (void) size;
   (void) format;
#endif
}
