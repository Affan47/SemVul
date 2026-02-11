shepherd_panic(const char *s)
{
   FILE *panic_fp;
   char panic_file[255];

   sprintf(panic_file, "/tmp/shepherd."pid_t_fmt, getpid());
   panic_fp = fopen(panic_file, "a");
   if (panic_fp) {
      dstring ds;
      char buffer[128];

      sge_dstring_init(&ds, buffer, sizeof(buffer));
      fprintf(panic_fp, "%s ["uid_t_fmt":"uid_t_fmt" "pid_t_fmt"]: PANIC: %s\n",
           sge_ctime(0, &ds), getuid(), geteuid(), getpid(), s);
      FCLOSE(panic_fp);
   }
FCLOSE_ERROR:
   return;
}
